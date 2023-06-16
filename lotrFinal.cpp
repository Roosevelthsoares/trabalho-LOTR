#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cctype>
#include <random>

using namespace std;

class Soldado{
    friend ostream& operator<<(ostream &os, const Soldado &s);

    protected:
        string nome;
        int saude;
        int vida_inicial;
        int poder_ataque;

    public:
        Soldado(string nome, int saude, int poder_ataque):
            nome(nome), saude(saude),vida_inicial(saude), poder_ataque(poder_ataque){}

        Soldado(const Soldado &p):
            nome(p.nome), saude(p.saude), vida_inicial(p.saude), poder_ataque(p.poder_ataque){}
        
        virtual ~Soldado(){}

        virtual void atacar(Soldado &enemy){ //necessário passar por referêcia para modificar o valor
            int dano = poder_ataque;
            defender(enemy, dano);
        }

        virtual void defender(Soldado &enemy, int dano){
            enemy.saude -=  dano;
            if(enemy.saude < 0){
                enemy.saude = 0;
            }
        }

        string getNome(){return nome;}

        int getSaude(){return saude;}
        void setSaude(int p){ saude = p;}

        int getVidaInicial(){return vida_inicial;}
        void setVidaInicial(int &p){ vida_inicial = p;}

        int getPoder(){return poder_ataque;}
};

class Elfo: public Soldado{
    public:
        Elfo(string nome, int saude, int poder_ataque):
            Soldado(nome, saude, poder_ataque + 1){}
        
        virtual ~Elfo(){}

        virtual void atacar(Soldado &enemy){
            srand(time(0));
            mt19937 gen(rand());

            int limiteInferior = (int)(poder_ataque - (poder_ataque *= 0.2));
            int limiteSuperior = (int)(poder_ataque + (poder_ataque *= 0.2));

            uniform_int_distribution<int> distribuicao(limiteInferior, limiteSuperior);

            int dano = distribuicao(gen);
            Soldado::defender(enemy, dano);
        }

        virtual void defender(Elfo &elfo, int dano){
            srand(time(0));
            int chance = 1 + rand() % 100;
            int defesa = 1 + rand() % 3;

            switch(defesa){
                case 1:{ /* CHANCE DE BLOQUEIO 10% */
                    if(chance >= 1 && chance <= 10){
                        cout<<"O elfo "<< elfo.nome <<" BLOQUEOU o ataque."<<endl;
                    }
                    else{
                        elfo.saude -=  dano;
                        if(elfo.saude < 0){
                            elfo.saude = 0;
                        }
                    }
                    break;
                }
                case 2:{ /* CHANCE DE DESVIO 30% */
                    if(chance >= 1 && chance <= 30){
                        cout<<"O elfo "<< elfo.nome <<" DESVIOU o ataque."<<endl;
                    }
                    else{
                        elfo.saude -=  dano;
                        if(elfo.saude < 0){
                            elfo.saude = 0;
                        }
                    }
                    break;
                }
                case 3:{ /* CHANCE DE CONTRA-ATAQUE 20% ( PENSAR COMO CONTRA-ATACAR) */
                    if(chance >= 1 && chance <= 20){
                        cout<<"O elfo "<< elfo.nome <<" CONTRA ATACOU."<<endl;
                        // this->atacar();
                    }
                    break;
                }
            }
        }
};

class Anao:public Soldado{
    public:
        Anao(string nome, int saude, int poder_ataque):
            Soldado(nome, saude, poder_ataque + 20){}
        
        virtual ~Anao(){}
            
        virtual void atacar(Soldado &enemy){ //necessário passar por referêcia para modificar o valor
            srand(time(0));
            int chance = (1+rand()%100);
            
            if(chance >= 1 && chance <= 40){ //chance de errar
                cout<<"O anao "<<this->nome<<" ERROU o ataque!"<<endl;
            }
            else{
                mt19937 gen(rand());

                int limiteInferior = (int)(poder_ataque - (poder_ataque *= 0.2));
                int limiteSuperior = (int)(poder_ataque + (poder_ataque *= 0.2));

                uniform_int_distribution<int> distribuicao(limiteInferior, limiteSuperior);

                int dano = distribuicao(gen);
                Soldado::defender(enemy, dano);
            }
        }

        virtual void defender(Anao &anao, int dano){
            srand(time(0));
            int chance = 1 + rand() % 100;
            int defesa = 1 + rand() % 3;

            switch(defesa){
                case 1:{ /* CHANCE DE BLOQUEIO 30% */
                    if(chance >= 1 && chance <= 30){
                        cout<<"O anao "<< anao.nome <<" BLOQUEOU o ataque."<<endl;
                    }
                    else{
                        anao.saude -=  dano;
                        if(anao.saude < 0){
                            anao.saude = 0;
                        }
                    }
                    break;
                }
                case 2:{ /* CHANCE DE DESVIO 10% */
                    if(chance >= 1 && chance <= 10){
                        cout<<"O anao "<< anao.nome <<" DESVIOU o ataque."<<endl;
                    }
                    else{
                        anao.saude -=  dano;
                        if(anao.saude < 0){
                            anao.saude = 0;
                        }
                    }
                    break;
                }
                case 3:{ /* CHANCE DE CONTRA-ATAQUE 10% */

                    break;
                }
            }
        }
};

class Humano:public Soldado{
    public:
        Humano(string nome, int saude, int poder_ataque):
            Soldado(nome, saude, poder_ataque){}
        
        virtual ~Humano(){}

        virtual void atacar(Soldado &enemy){
            srand(time(0));
            int chance = (1+rand()%100);
            
            mt19937 gen(rand());

            int limiteInferior = (int)(poder_ataque - (poder_ataque *= 0.2));
            int limiteSuperior = (int)(poder_ataque + (poder_ataque *= 0.2));

            uniform_int_distribution<int> distribuicao(limiteInferior, limiteSuperior);

            int dano = distribuicao(gen);
            
            if(chance >= 1 && chance <= 10){ //chance de ataque duplo 10%
                dano *= 2;
            }
            Soldado::defender(enemy, dano);
        }

        virtual void defender(Humano &humano, int dano){
            srand(time(0));
            int chance = 1 + rand() % 100;
            int defesa = 1 + rand() % 3;

            switch(defesa){
                case 1:{ /* CHANCE DE BLOQUEIO 10% */
                    if(chance >= 1 && chance <= 10){
                        cout<<"O humano "<< humano.nome <<" BLOQUEOU o ataque."<<endl;
                    }
                    else{
                        humano.saude -=  dano;
                        if(humano.saude < 0){
                            humano.saude = 0;
                        }
                    }
                    break;
                }
                case 2:{ /* CHANCE DE DESVIO 20% */
                    if(chance >= 1 && chance <= 20){
                        cout<<"O humano "<< humano.nome <<" DESVIOU o ataque."<<endl;
                    }
                    else{
                        humano.saude -=  dano;
                        if(humano.saude < 0){
                            humano.saude = 0;
                        }
                    }
                    break;
                }
                case 3:{ /* CHANCE DE CONTRA-ATAQUE 30% */

                    break;
                }
            }
        }
};

class Orc: public Soldado{
    public:
        Orc(string nome, int saude, int poder_ataque):
            Soldado(nome, saude, poder_ataque * 1.1){} //10% de bonus de poder de ataque
        
        virtual ~Orc(){}

        virtual void atacar(Soldado &enemy){
            srand(time(0));
            int chance = (1+rand()%100);
            
            mt19937 gen(rand());

            int limiteInferior = (int)(poder_ataque - (poder_ataque *= 0.2));
            int limiteSuperior = (int)(poder_ataque + (poder_ataque *= 0.2));

            uniform_int_distribution<int> distribuicao(limiteInferior, limiteSuperior);
            int dano = distribuicao(gen);

            if(chance >= 1 && chance <= 20){ // 20% de chance de ataque duplo
                dano *= 2;
            }
            Soldado::defender(enemy, dano);
        }

        virtual void defender(Orc &orc, int dano){
            srand(time(0));
            int chance = 1 + rand() % 100;
            int defesa = 1 + rand() % 3;

            switch(defesa){
                case 1:{ /* CHANCE DE BLOQUEIO 20% */
                    if(chance >= 1 && chance <= 20){
                        cout<<"O orc "<< orc.nome <<" BLOQUEOU o ataque."<<endl;
                    }
                    else{
                        orc.saude -=  dano;
                        if(orc.saude < 0){
                            orc.saude = 0;
                        }
                    }
                    break;
                }
                case 2:{ /* CHANCE DE DESVIO 20% */
                    if(chance >= 1 && chance <= 20){
                        cout<<"O orc "<< orc.nome <<" DESVIOU o ataque."<<endl;
                    }
                    else{
                        orc.saude -=  dano;
                        if(orc.saude < 0){
                            orc.saude = 0;
                        }
                    }
                    break;
                }
                case 3:{ /* CHANCE DE CONTRA-ATAQUE 20% */

                    break;
                }
            }
        }
};

class Sauron: public Soldado{
    public:
        Sauron(string nome, int saude, int poder_ataque):
            Soldado(nome, saude*10, poder_ataque){}

        virtual ~Sauron(){}

        virtual void atacar(Soldado &enemy){
            srand(time(0));
            int chance = (1+rand()%100);
            
            mt19937 gen(rand());

            int limiteInferior = (int)(poder_ataque - (poder_ataque *= 0.2));
            int limiteSuperior = (int)(poder_ataque + (poder_ataque *= 0.2));

            uniform_int_distribution<int> distribuicao(limiteInferior, limiteSuperior);
            int dano = distribuicao(gen);

            if(chance >= 1 && chance <= 30){ //30% de chance de acertar um ataque duplo
                dano *= 2;
            }
            Soldado::defender(enemy, dano);
        }

        virtual void defender(Sauron &sauron, int dano){
            srand(time(0));
            int chance = 1 + rand() % 100;
            int defesa = 1 + rand() % 3;

            int defesa = 1 + rand() % 3;
            switch(defesa){
                case 1:{ /* CHANCE DE BLOQUEIO 30% */
                    if(chance >= 1 && chance <= 30){
                        cout<< sauron.nome <<" BLOQUEOU o ataque."<<endl;
                    }
                    else{
                        sauron.saude -=  dano;
                        if(sauron.saude < 0){
                            sauron.saude = 0;
                        }
                    }
                    break;
                }
                case 2:{ /* CHANCE DE DESVIO 10% */
                    if(chance >= 1 && chance <= 10){
                        cout<< sauron.nome <<" DESVIOU o ataque."<<endl;
                    }
                    else{
                        sauron.saude -=  dano;
                        if(sauron.saude < 0){
                            sauron.saude = 0;
                        }
                    }
                    break;
                }
                case 3:{ /* CHANCE DE CONTRA-ATAQUE 30% */

                    break;
                }
            }
        }
};

class Mago: public Soldado{ 
    public:
        Mago(string nome, int saude, int poder_ataque):
            Soldado(nome, saude * 9, poder_ataque * 3){}

        virtual ~Mago(){}

        virtual void atacar(Soldado &enemy){
            srand(time(0));
            int chance = (1+rand()%100);
            
            mt19937 gen(rand());

            int limiteInferior = (int)(poder_ataque - (poder_ataque *= 0.2));
            int limiteSuperior = (int)(poder_ataque + (poder_ataque *= 0.2));

            uniform_int_distribution<int> distribuicao(limiteInferior, limiteSuperior);
            int dano = distribuicao(gen);

            if(chance >= 1 && chance <= 50){ // 50% de chance de ataque duplo
                dano *= 2;
            }
            Soldado::defender(enemy, dano);
        }

        virtual void defender(Mago &mago, int dano){
            srand(time(0));
            int chance = 1 + rand() % 100;
            int defesa = 1 + rand() % 3;

            switch(defesa){
                case 1:{ /* CHANCE DE BLOQUEIO 10% */
                    if(chance >= 1 && chance <= 10){
                        cout<< mago.nome <<" BLOQUEOU o ataque."<<endl;
                    }
                    else{
                        mago.saude -=  dano;
                        if(mago.saude < 0){
                            mago.saude = 0;
                        }
                    }
                    break;
                }
                case 2:{ /* CHANCE DE DESVIO 30% */
                    if(chance >= 1 && chance <= 30){
                        cout<< mago.nome <<" DESVIOU o ataque."<<endl;
                    }
                    else{
                        mago.saude -=  dano;
                        if(mago.saude < 0){
                            mago.saude = 0;
                        }
                    }
                    break;
                }
                case 3:{ /* CHANCE DE CONTRA-ATAQUE 30% */

                    break;
                }
            }
        }
};

class Bem{
    protected:
        void poderProtagonista(){

        }

        void ataqueCombinado(){

        }

};

class Mal{
    protected:

};

class MuitoMal{
    protected:

};

Soldado batalha(vector<Soldado> &vec){
    int cont = 1;
    while(vec.size() > 1){
        srand(time(NULL));
        random_shuffle(vec.begin(), vec.end());

        auto it = vec.rbegin();
        Soldado guerreiro1 = *it;
        vec.pop_back();

        it = vec.rbegin();
        Soldado guerreiro2 = *it;
        vec.pop_back();
        
        cout<<"==========> Batalha "<<cont<<" <=========="<<endl;
        while(true){
            guerreiro1.atacar(guerreiro2);
            cout<< guerreiro1.getNome() <<" atacou "<< guerreiro2 <<". Agora "<< guerreiro2 << " tem "<<guerreiro2.getSaude()<<" de vida."<<endl;
            if (guerreiro2.getSaude() == 0){
                cout<<guerreiro2.getNome()<<" esta morto."<<endl;
                vec.push_back(guerreiro1);
                break;
            }
            guerreiro2.atacar(guerreiro1);
            cout<< guerreiro2.getNome() <<" atacou "<< guerreiro1 <<". Agora "<< guerreiro1 << " tem "<<guerreiro1.getSaude()<<" de vida."<<endl;
            if (guerreiro1.getSaude() == 0){
                cout<<guerreiro1.getNome()<<" esta morto."<<endl;
                vec.push_back(guerreiro2);
                break;
            }
        }
        cout<<"Vencedor da batalha "<< cont <<": ";
        if(guerreiro1.getSaude() > 0){
            cout<<guerreiro1.getNome()<<endl;
            cout<<"\n\n"<<endl;

        }
        else if(guerreiro2.getSaude() > 0){
            cout<<guerreiro2.getNome();
            cout<<"\n\n"<<endl;
        }

        cont++;
    }

    return vec.at(0);
}

ostream& operator<<(ostream &os, const Soldado &s){
    os << s.nome;
    return os;
}


int main(){
    Mago gandalf("Gandalf", 100, 20);
    Sauron sauron("Sauron", 100, 50);

    Orc O1("O1", 100, 10);
    Orc O2("O2", 100, 10);
    Orc O3("O3", 100, 10);
    Orc O4("O4", 100, 10);
    Orc O5("O5", 100, 10);
    Orc O6("O6", 100, 10);
    Orc O7("O7", 100, 10);
    Orc O8("O8", 100, 10);
    Orc O9("O9", 100, 10);
    Orc O10("O10", 100, 10);

    Elfo E1("E1", 100, 20);
    Elfo E2("E2", 100, 20);
    Elfo E3("E3", 100, 20);
    Elfo E4("E4", 100, 20);
    Elfo E5("E5", 100, 20);

    Humano H1("H1", 100, 20);
    Humano H2("H2", 100, 20);
    Humano H3("H3", 100, 20);
    Humano H4("H4", 100, 20);
    Humano H5("H5", 100, 20);

    Anao A1("A1",100, 20);
    Anao A2("A2",100, 20);
    Anao A3("A3",100, 20);
    Anao A4("A4",100, 20);
    Anao A5("A5",100, 20);


    vector<Soldado> guerreiros {
        gandalf,
        sauron,
        O1,
        O2,
        O3,
        O4,
        O5,
        O6,
        O7,
        O8,
        O9,
        O10,
        E1,
        E2,
        E3,
        E4,
        E5,
        H1,
        H2,
        H3,
        H4,
        H5,
        A1,
        A2,
        A3,
        A4,
        A5
    };

    Soldado vencedor = batalha(guerreiros);
    string nomeVencedor = vencedor.getNome();
    transform(nomeVencedor.begin(), nomeVencedor.end(), nomeVencedor.begin(), ::toupper);
    cout<<"\n\n\nO grande vencedor da batalha eh "<< nomeVencedor <<"!"<<endl;

    return 0;
}