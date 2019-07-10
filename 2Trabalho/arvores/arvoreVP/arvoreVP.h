#ifndef _arvoreVP_H_
#define _arvoreVP_H_
#include <string>
#include <iostream>
#include "no.h"

class arvoreVP {

    public:
    arvoreVP();//Construtor padrao
    ~arvoreVP();//Destrutor padrao
    bool buscarValor(int chave);//Busca um valor na arvore(T:existe/ F:nao existe na arvore)
    void inserirValor(no* novaChave, int* comparacoes, int* trocas);//Insere a chave na arvore
    void fixUp(no* noAtual);// Verifica e ajusta a arvore para manter as propriedades apos uma insercao
    void setRaiz(no* raizNova);// Define uma nova raiz
    void leftRotate(no* noAtual);//Faz a rotacao do no atual e seus filhos para a esquerda
    void rightRotate(no* noAtual);// Faz a rotacao do no atual e seus filhos para a direita
    int numeroComparacoes; //Numero de comparacoes 
    int numeroTrocas; //Numero de trocas
    private:

    no* raiz; //Raiz da arvore
    no* sentinela;// No de cor preta que eh filho de todas as folhas e pai da raiz

};
#endif