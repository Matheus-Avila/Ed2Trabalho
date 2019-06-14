#include <iostream>
#include <string>
#include <cmath>
#include "pagina.h"

using namespace std;

pagina::pagina(){
    //Construtor padrao
}

//Construtor completo
pagina::pagina(int ordem, pagina* pai){
    this->posOcupadas = 0;
    this->chaves = new chave[2*ordem];
    this->paginasFilhas = new pagina*[2*ordem+1]; //Ta certo???
    this->paginaPai = pai;

}

//Destrutor
pagina::~pagina(){
    //Destrutor
}

//Retorna numero de chaves ocupadas
int pagina::getPosOcupadas(){
    return posOcupadas;
}

//Retorna a ordem da pagina
int pagina::getOrdem(){
    return this->ordem;
}

//Testa se existem chaves disponiveis na pagina(T: Cheia/ F: PosLivre)
bool pagina::paginaCheia(){
    return getPosOcupadas() == 2*getOrdem();
}

//Divide a pagina cheia se tentar inserir
void pagina::splitPagina(){

}

//Testa se a página eh a raiz
bool pagina::eRaiz(){
    return this->paginaPai == NULL;
}

//Define o pai de uma pagina
void pagina::setPai(pagina* pai){
    paginaPai = pai;
}

//Retorna a chave na posicao pos
chave* pagina::getChave(int pos){
    return &chaves[pos];
}

//Retorna a pagina filha da chave na posicao pos
pagina* pagina::getFilha(int pos){
    return paginasFilhas[pos];
}