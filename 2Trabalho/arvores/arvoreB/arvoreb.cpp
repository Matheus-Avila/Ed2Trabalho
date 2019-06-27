#include "arvoreb.h"
#include "chave.h"
#include "pagina.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

arvoreb::arvoreb(){
    //Construtor padrao
}

//Construtor completo
arvoreb::arvoreb(int ordem){
    this->ordem = ordem;
    this->numeroComparacoes = 0;
    this->numeroTrocas = 0;
    raiz = new pagina(ordem, NULL);
}

arvoreb::~arvoreb(){
    //Destrutor
}

//Retorna a ordem da arvore
int arvoreb::getOrdem(){
    return ordem;
}

bool arvoreb::buscaChave(int chave){
    pagina* busca = raiz;
    int posOcupadas;// Armazena a qtde de chaves armazenadas
    int count;// Variavel para percorrer o vetor de chaves de cada pagina
    while(busca != NULL){
        if(busca->getPosOcupadas() == 0){//Se a pagina estiver vazia pare a verificacao
            break;
        }
        posOcupadas = busca->getPosOcupadas();
        count = 0;// Reseta o contador para a proxima pagina
        //Percorre a pagina e verifica se a chave eh maior que o chaves->valor
        while(count < posOcupadas && chave > busca->getChave(count)->getValor()){
            count ++;
        }
        //Sai quando chegar ao fim ou se chegar em uma chave maior que a procurada
        //Se a chave for igual a procurada retorna true
        if(count < posOcupadas && chave == busca->getChave(count)->getValor()){
            return true;
        }//A chave eh menor que o chaves[count]->valor ou chegou ao fim da pagina
        else{//procura no filho que está no count
            busca = busca->getFilha(count); 
        }

    }
    return false; // Nao encontrou a chave procurada
}

//Insere uma chave na arvore
void arvoreb::inserirChave(chave* movie, int *comparacoes, int *trocas){
    //remover pai, a verificacao da raiz eh desnecessaria
    pagina* busca = raiz;
    int posOcupadas;// Armazena a qtde de chaves armazenadas
    int count;// Variavel para percorrer o vetor de chaves de cada pagina
    while(busca != NULL){
        if(busca->getPosOcupadas() == 0){//Se a pagina estiver vazia pare a verificacao
            break;
        }
        posOcupadas = busca->getPosOcupadas();
        count = 0;// Reseta o contador para a proxima pagina
        //Percorre a pagina e verifica se a chave eh maior que o chaves->valor
        while(count < posOcupadas && movie->getValor() > busca->getChave(count)->getValor()){
            count ++;
            //Sai quando chegar ao fim ou se chegar em uma chave maior que a movie.Valor
        }
        
        //procura no filho que está no count
        //Se for nulo chegou na folha e devemos inserir
        if(busca->getFilha(count)==NULL){
            break;
        }
        busca = busca->getFilha(count); 
        
    }
    busca->inserirNaFolha(movie);
    //Enquanto tiver paginas lotadas divida
    while(busca->getPosOcupadas > 2*busca->getOrdem()){
        
        busca->splitPagina();
        busca = busca->getPai();
    
    }
}