#ifndef _no_H_
#define _no_H_
#include <string>
#include <iostream>
class no{
    
    public:
    no();//Construtor padrao
    no(float valor, float rating, long int timestamp);//Construtor completo
    ~no();//Destrutor padrao
    void setCor(int cor);//Define a cor do no
    int getCor();//Retorna a cor do no
    float getValor(); //Retorna valor da chave
    float getRating(); //Retorna rating da chave
    long int getTimeStamp(); // Retorna timestamp da chave
    void setPai(no* pai);// Define o pai do no
    no* getPai();// Retorna o pai do no
    void setFilhoEsq(no* filho);// Define o filho a esquerda do no
    void setFilhoDir(no* filho);// Define o filho a direita do no
    no* getFilhoEsq();// Retorna o filho a esquerda do no
    no* getFilhoDir();// Retorna o filho a direita do no
    bool naoEhSentinela();//Verifica se o no eh o no sentinela

    private:
    float valor; //Chave para busca
    float rating; //Rating da chave
    long int timestamp; //TimeStamp da chave
    int cor; //Cor do no(0: vermelho/1: preto) 2: Sentinela
    no* filhoEsq;//Filho esquerdo do no
    no* filhoDir;//Filho direito do no
    no* pai;//Pai do no
};
#endif