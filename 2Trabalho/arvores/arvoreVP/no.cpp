#include "no.h"
#include "arvoreVP.h"

using namespace std;

//Construtor padrao
no::no(){
    
    this->cor = 0;//Define a cor como vermelha
}

//Construtor completo
no::no(float valor, float rating, long int timestamp){
    this->valor = valor;
    this->rating = rating;
    this->timestamp = timestamp;
    this->cor = 0;//Define a cor como vermelha
}

no::~no(){
    //Destrutor padrao
}

//Define a cor do no
void no::setCor(int cor){
    this->cor = cor; 
}

//Retorna a cor do no
int no::getCor(){
    return this->cor;
}

//Retorna valor da chave
float no::getValor(){
    return this->valor;
}

//Retorna rating da chave
float no::getRating(){
    return this->rating;
}

// Retorna timestamp da chave
long int no::getTimeStamp(){
    return this->getTimeStamp;
}

// Define o pai do no
void no::setPai(no* pai){
    this->pai = pai;
}

// Retorna o pai do no
no* no::getPai(){
    return this->pai;
}

// Define o filho a esquerda do no
void no::setFilhoEsq(no* filho){
    this->filhoEsq = filho;
    //filho->setPai(this);
}

// Define o filho a direita do no
void no::setFilhoDir(no* filho){
    this->filhoDir = filho;
    //filho->setPai(this);
}

// Retorna o filho a esquerda do no
no* no::getFilhoEsq(){
    return this->filhoEsq;
}

// Retorna o filho a direita do no
no* no::getFilhoDir(){
    return this->filhoDir;
}

// Faz a rotacao do no atual e seus filhos para a esquerda
//Eu supus que this->filhoDir eh diferente de sentinela pois so sera
//necessario executar leftRotate se this->filhoDir for diferente de sentinela
void no::leftRotate(arvoreVP* arvore){
    no* y = this->getFilhoDir();//Passar referencia ou valor??
    this->setFilhoDir(y->getFilhoEsq());
    if(y->getFilhoEsq()->naoEhSentinela()){
        y->getFilhoEsq()->setPai(this);
    }
    y->setPai(this->getPai());
    if(!this->getPai()->naoEhSentinela()){//this eh a raiz
        arvore->setRaiz(y);//y se torna a nova raiz
    }
    else{//Se this for filho a esquerda de seu pai
        //Da pra fazer comparando as chaves tbm
        if(this == this->getPai()->getFilhoEsq()){
            this->getPai()->setFilhoEsq(y);
        }
        else{
            this->getPai()->setFilhoDir(y);
        }
    }
    y->setFilhoEsq(this);
    this->setPai(y);
}

// Faz a rotacao do no atual e seus filhos para a direita
void no::rightRotate(arvoreVP* arvore){
    no* y = this->getFilhoDir();
    this->setFilhoEsq(y->getFilhoDir());
    if(y->getFilhoDir()->naoEhSentinela()){
        y->getFilhoDir()->setPai(this);
    }
    y->setPai(this->getPai());
    if(!this->getPai()->naoEhSentinela()){//this eh a raiz
        arvore->setRaiz(y);//y se torna a nova raiz
    }
    else{//Se this for filho a esquerda de seu pai
        //Da pra fazer comparando as chaves tbm
        if(this == this->getPai()->getFilhoEsq()){
            this->getPai()->setFilhoEsq(y);
        }
        else{
            this->getPai()->setFilhoDir(y);
        }

    }
    y->setFilhoDir(this);
    this->setPai(y);
}

//Verifica se o no que chamou a funcao nao eh o no sentinela
bool no::naoEhSentinela(){
    return this->getCor() != 2;
}