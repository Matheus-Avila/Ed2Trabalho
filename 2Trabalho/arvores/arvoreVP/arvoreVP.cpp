#include "arvoreVP.h"

using namespace std;

//Construtor padrao
arvoreVP::arvoreVP(){
    sentinela = new no();
    sentinela->setCor(2);
    raiz = sentinela;
    raiz->setFilhoEsq(sentinela);
    raiz->setFilhoDir(sentinela);
    numeroComparacoes = 0;
    numeroTrocas = 0;
}

arvoreVP::~arvoreVP(){
    //Destrutor padrao
}

// Define uma nova raiz
void arvoreVP::setRaiz(no* raizNova){
    raiz = raizNova;
}

//Busca um valor na arvore(T:existe/ F:nao existe na arvore)
bool arvoreVP::buscarValor(int chave){
    no* busca = raiz;
    while(busca!=sentinela){
        if(busca->getValor() == chave){
            return true;//Achou a chave procurada
        }
        if(chave > busca->getValor()){
            busca = busca->getFilhoDir();
        }
        else{
            busca = busca->getFilhoEsq();
        }
    }
    return false;//Nao achou a chave procurada
}

//Insere a chave na arvore
void arvoreVP::inserirValor(no* novaChave, int* comparacoes, int* trocas){
    no* busca = raiz;
    no* y = raiz->getPai();
    while(busca->naoEhSentinela()){
        y = busca;
        if(novaChave->getValor()< busca->getValor()){
            busca = busca->getFilhoEsq();
        }
        else{
            busca = busca->getFilhoDir();
        }
    }
    novaChave->setPai(y);
    if(!y->naoEhSentinela()){
        raiz = novaChave;
    }
    else{
        if(novaChave->getValor() < y->getValor()){
            y->setFilhoEsq(novaChave);
        }
        else{
            y->setFilhoDir(novaChave);
        }
    }
    //A nova folha tem como filho a sentinela
    novaChave->setFilhoDir(sentinela);
    novaChave->setFilhoEsq(sentinela);
    fixUp(novaChave);
}


//Apos inserir noAtual verifica se as propriedades se mantiveram 
// e realiza modificacoes para manter-las se necessario
//As propriedades que podem ser violadas sao:
//raiz preta
//no vermelho com filho vermelho
void arvoreVP::fixUp(no* noAtual){
    no* y;
    while(noAtual->getPai()->getCor() == 0){
        //Se o pai do noAtual for filho a esquerda de seu pai
        if(noAtual->getPai() == noAtual->getPai()->getPai()->getFilhoEsq()){
            //y eh tio a direita de noAtual
            y = noAtual->getPai()->getPai()->getFilhoDir();
            if(y->getCor() == 0){//Se o tio for vermelho
                //Muda as cores do pai, do avo, e do tio
                noAtual->getPai()->setCor(1);
                noAtual->getPai()->getPai()->setCor(0);
                y->setCor(1);
                noAtual = noAtual->getPai()->getPai();
            }
            else{//Se o no atual for filho a direita de seu pai
                if(noAtual == noAtual->getPai()->getFilhoDir()){
                    //Deixarei avo, pai e no alinhados a esquerda fazendo uma leftRotate
                    noAtual = noAtual->getPai();
                    noAtual->leftRotate(this);    
                    noAtual = noAtual->getFilhoEsq();//Ou nao????!!!!!!!!!! Cormen tira isso
                }
                //noAtual ja esta alinhado com avo e pai a esquerda
                noAtual->getPai()->setCor(1);
                noAtual->getPai()->getPai()->setCor(0);
                noAtual->getPai()->getPai()->rightRotate(this);
            }
        }
        //Se o pai do noAtual for filho a direita de seu pai
        else{
            //y eh tio a esquerda de noAtual
            y = noAtual->getPai()->getPai()->getFilhoEsq();
            if(y->getCor() == 0){//Se o tio for vermelho
                //Muda as cores do pai, do avo, e do tio
                noAtual->getPai()->setCor(1);
                noAtual->getPai()->getPai()->setCor(0);
                y->setCor(1);
                noAtual = noAtual->getPai()->getPai();
            }
            else{//Se o no atual for filho a esquerda de seu pai
                if(noAtual == noAtual->getPai()->getFilhoEsq()){
                    //Deixarei avo, pai e no alinhados a direita fazendo uma rightRotate
                    noAtual = noAtual->getPai();
                    noAtual->rightRotate(this);    
                    noAtual = noAtual->getFilhoDir();//Ou nao????!!!!!!!!!! Cormen tira isso
                }
                //noAtual ja esta alinhado com avo e pai a direita
                noAtual->getPai()->setCor(1);
                noAtual->getPai()->getPai()->setCor(0);
                noAtual->getPai()->getPai()->leftRotate(this);
            }
        }
    }
    this->raiz->setCor(1);
}