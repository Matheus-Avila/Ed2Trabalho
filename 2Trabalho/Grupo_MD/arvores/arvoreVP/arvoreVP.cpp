#include "arvoreVP.h"

using namespace std;

//Construtor padrao
arvoreVP::arvoreVP(){
    sentinela = new no();
    sentinela->setCor(2);
    sentinela->setPai(NULL);
    raiz = sentinela;
    raiz->setFilhoEsq(sentinela);
    raiz->setFilhoDir(sentinela);
    raiz->setPai(sentinela);
    numeroComparacoes = 0;
    numeroTrocas = 0;
}

arvoreVP::~arvoreVP(){
    no* busca = raiz;
    no* y = sentinela;
    while(busca->naoEhSentinela()){
        if(busca->getFilhoEsq()->naoEhSentinela()){
            y = busca;
            busca = busca->getFilhoEsq();
        }
        else{
            if(busca->getFilhoDir()->naoEhSentinela()){
                y = busca;
                busca = busca->getFilhoDir();
            }
            else{
                delete busca;
                busca = y;
            }
        }
    }
    delete raiz;
    delete sentinela;
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
    y->naoEhSentinela();
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

// Faz a rotacao do no atual e seus filhos para a esquerda
//Eu supus que this->filhoDir eh diferente de sentinela pois so sera
//necessario executar leftRotate se this->filhoDir for diferente de sentinela
//Faz a rotacao do no atual e seus filhos para a esquerda
void arvoreVP::leftRotate(no* noAtual){
    no* y = noAtual->getFilhoDir();
    noAtual->setFilhoDir(y->getFilhoEsq());
    if(y->getFilhoEsq()->naoEhSentinela()){
        y->getFilhoEsq()->setPai(noAtual);
    }
    y->setPai(noAtual->getPai());
    if(!noAtual->getPai()->naoEhSentinela()){//noAtual eh a raiz
        this->setRaiz(y);//y se torna a nova raiz
    }
    else{//Se noAtual for filho a esquerda de seu pai
        //Da pra fazer comparando as chaves tbm
        if(noAtual == noAtual->getPai()->getFilhoEsq()){
            noAtual->getPai()->setFilhoEsq(y);
        }
        else{
            noAtual->getPai()->setFilhoDir(y);
        }
    }
    y->setFilhoEsq(noAtual);
    noAtual->setPai(y);
}

//Faz a rotacao do no atual e seus filhos para a direita
void arvoreVP::rightRotate(no* noAtual){
    no* y = noAtual->getFilhoDir();
    noAtual->setFilhoEsq(y->getFilhoDir());
    if(y->getFilhoDir()->naoEhSentinela()){
        y->getFilhoDir()->setPai(noAtual);
    }
    y->setPai(noAtual->getPai());
    if(!noAtual->getPai()->naoEhSentinela()){//noAtual eh a raiz
        this->setRaiz(y);//y se torna a nova raiz
    }
    else{//Se noAtual for filho a esquerda de seu pai
        if(noAtual == noAtual->getPai()->getFilhoEsq()){
            noAtual->getPai()->setFilhoEsq(y);
        }
        else{
            noAtual->getPai()->setFilhoDir(y);
        }

    }
    y->setFilhoDir(noAtual);
    noAtual->setPai(y);
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
                    this->leftRotate(noAtual);    
                }
                //noAtual ja esta alinhado com avo e pai a esquerda
                noAtual->getPai()->setCor(1);
                noAtual->getPai()->getPai()->setCor(0);
                this->rightRotate(noAtual->getPai()->getPai());
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
                    this->rightRotate(noAtual);    
                }
                //noAtual ja esta alinhado com avo e pai a direita
                noAtual->getPai()->setCor(1);
                noAtual->getPai()->getPai()->setCor(0);
                this->leftRotate(noAtual->getPai()->getPai());
            }
        }
    }
    this->raiz->setCor(1);
}