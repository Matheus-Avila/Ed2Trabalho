#include "nohf.h"

using namespace std;

//Construtor padrao
nohf::nohf(){
    this->pai = -1;
    this->filhoDir = -1;
    this->filhoEsq = -1;
    this->frequencia = 0;
}

//Construtor completo
nohf::nohf(char c){
    this->caractere = c;
    this->frequencia = 1;
    this->pai = -1;
    this->filhoDir = -1;
    this->filhoEsq = -1;
}


//Destrutor padrao
nohf::~nohf(){

}

//Verifica se tem pai(T: tem pai/F: nao tem)
bool nohf::temPai(){

    return this->pai!= -1;
}


char nohf::getCaractere(){
    return this->caractere;
}

int nohf::getFilhoDir(){
    return filhoDir;
}

int nohf::getFilhoEsq(){
    return filhoEsq;
}

int nohf::getPai(){
    return this->pai;
}

void nohf::setFilhoDir(int i){
    this->filhoDir = i;
}

void nohf::setFilhoEsq(int i){
    this->filhoEsq = i;
}

void nohf::setPai(int i){
    this->pai = i;
}

void nohf::setFrequencia(int i){
    this->frequencia = i;
}

int nohf::getFrequencia(){
    return this->frequencia;
}

void nohf::addFrequencia(){
    this->frequencia++;
}