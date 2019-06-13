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

//Construtor
arvoreb::arvoreb(int ordem){
    this->ordem = ordem;
    raiz = new pagina();
}

arvoreb::~arvoreb(){
    //Destrutor
}

bool arvoreb::buscaChave(int chave){
    pagina* busca = raiz;
    int posOcupadas;
    int count;
    while(busca != NULL){
        if(busca->getPosOcupadas() == 0){//Se a pagina estiver vazia para
            break;
        }
        posOcupadas = busca->getPosOcupadas();
        count = 0;
        //Percorre a pagina e verifica se a chave eh maior que o chaves->valor
        while(count < posOcupadas && chave > busca->getChave(count)->getValor()){
            count ++;
        }
        //Sai quando chegar ao fim ou se chegar em uma chave maior que a procurada
        //Se a chave for igual a procurada retorna true
        if(count < posOcupadas && chave == busca->getChave(count)->getValor()){
            return true;
        }//A chave eh menor que o chaves->valor ou chegou ao fim da pagina
        else{//procura no filho que está na posOcupadas
            busca = busca->getFilha(posOcupadas); 
        }

    }
    return false; // Nao encontrou a chave procurada
}