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
    this->chaves = new chave[2*ordem+1]; //A ultima posicao eh usada para realizar o split
    this->paginasFilhas = new pagina*[2*ordem+2];//A ultima posicao eh usada para realizar o split
    this->paginaPai = pai;
    for(int i = 0; i <= 2*ordem+1; i++){
        this->paginasFilhas[i] = NULL;//Inicializando com NULL para evitar
    }

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

//Apos o split, sobe a chave e o novo filho para o pai
void pagina::subirChave(chave chave, pagina* filha){//filha eh a filha a direita de chave
    //percorre pai procurando o lugar que a chave nova vai ficar
    int i;
    for(i = this->getPosOcupadas()-1; i >= -1; i--){
        //i = -1 indica que i percorreu a pagina e nao achou uma chave menor que chaveNova,
        //logo, a chave nova deve ser inserida na posicao 0
        if(i != -1 && chave.getValor() < this->getChave(i)->getValor()){
            //se der segmantetion fault altere esse if!!!!!!!!!!!!!!
            this->chaves[i+1] = this->chaves[i];//Move a chave para frente
            this->paginasFilhas[i+2] = this->paginasFilhas[i+1];//Move a filha a direita de
            //i para frente

        }
        else{
            this->chaves[i+1] = chave;//Insere a chave na posicao
            this->paginasFilhas[i+2] = filha;//Insere a filha na posicao a direita
            break;//Encontramos a posicao da chaveNova, portanto paramos a execucao
        }
    }
}

//Antes de inserir um valor ordena as chaves da folha, e insere a chave
void pagina::inserirNaFolha(chave chaveNova){
    //Percorre a partir do final, buscando a posicao da chaveNova
    for(int i = posOcupadas-1; i >= -1; i--){
        //i = -1 indica que i percorreu a pagina e nao achou uma chave menor que chaveNova,
        //logo, a chave nova deve ser inserida na posicao 0
        if(chaveNova.getValor() < this->getChave(i)->getValor() && i != -1){
            
            this->chaves[i+1] = this->chaves[i];//Move a chave para frente
        }
        else{
            this->chaves[i+1] = chaveNova;//Insere a chave na posicao
            break;//Encontramos a posicao da chaveNova, portanto paramos a execucao
        }

    }

}


//Divide a pagina lotada 
void pagina::splitPagina(){
    if(eRaiz()){
        pagina* raizNova = new pagina(getOrdem(), NULL);//Cria uma nova raiz
        this->setPai(raizNova);// O pai da antiga raiz eh raizNova
        //Nova pagina filha com a metade maior das chaves e filhas de this
        pagina *filhaNova = new pagina(getOrdem(), this->getPai());
        int i;
        for(i = getOrdem()+1; i < getPosOcupadas(); i++){
            filhaNova->chaves[i-getOrdem()-1] = this->chaves[i];
            filhaNova->paginasFilhas[i-getOrdem()-1] = this->paginasFilhas[i];
            this->posOcupadas--;
            filhaNova->posOcupadas++;

        }
        //passar ultimo ponteiro
        filhaNova->paginasFilhas[i-getOrdem()-1] = this->paginasFilhas[i];
        //Sobe a chave intermediaria para o pai e aualiza posOcupadas
        this->getPai()->subirChave(chaves[getOrdem()], filhaNova);
        this->getPai()->posOcupadas++;
        this->posOcupadas--;

    }else{
        //Nova pagina filha com a metade maior das chaves e filhas de this
        pagina *filhaNova = new pagina(getOrdem(), this->getPai());
        if(!this->NoIntermediario){
            for(int i = getOrdem()+1; i < getPosOcupadas(); i++){
                filhaNova->chaves[i-getOrdem()-1] = this->chaves[i];
                this->posOcupadas--;
                filhaNova->posOcupadas++;

            }
            
        }
        //Caso o split seja em uma pagina intermediaria
        else{
            int i;
            for(i = getOrdem()+1; i < getPosOcupadas(); i++){
                filhaNova->chaves[i-getOrdem()-1] = this->chaves[i];
                filhaNova->paginasFilhas[i-getOrdem()-1] = this->paginasFilhas[i];
                this->posOcupadas--;
                filhaNova->posOcupadas++;

            }
            //passar ultimo ponteiro
            filhaNova->paginasFilhas[i-getOrdem()-1] = this->paginasFilhas[i];
            
        }
        //Sobe a chave intermediaria para o pai e aualiza posOcupadas
        this->getPai()->subirChave(chaves[getOrdem()], filhaNova);
        this->getPai()->posOcupadas++;
        this->posOcupadas--;
    }
}

//Testa se a página eh a raiz
bool pagina::eRaiz(){
    return this->paginaPai == NULL;
}

//Define o pai de uma pagina
void pagina::setPai(pagina* pai){
    paginaPai = pai;
}

//Retorna o pai da pagina
pagina* pagina::getPai(){
    return paginaPai;
}

//Retorna a chave na posicao pos
chave* pagina::getChave(int pos){
    return &chaves[pos];
}

//Retorna a pagina filha da chave na posicao pos
pagina* pagina::getFilha(int pos){
    return paginasFilhas[pos];
}