#include <iostream>
#include <string>
#include <cmath>
#include "arvoreb.h"
#include "pagina.h"
using namespace std;

arvoreb::arvoreb(){
    //Construtor padrao
}

//Construtor completo
arvoreb::arvoreb(int ordem){
    
    this->ordem = ordem;
    this->numeroComparacoes = 0;
    this->numeroTrocas = 0;
    raiz = new pagina(ordem, NULL);cout << "criando arvore" << this->ordem << endl;
}

arvoreb::~arvoreb(){cout << "destruido arvore" << endl;
    pagina* busca = raiz;
    pagina* y = NULL;

    int posOcupadas;// Armazena a qtde de chaves armazenadas
    int count;// Variavel para percorrer o vetor de chaves de cada pagina
    while(busca != NULL){
        if(busca->getFilha(0) == NULL){//Se for folha deleta e vai para o pai
            
            delete busca;            
            busca = y;
        }else{
            count = 0;//procura o filho mais a direita que e diferente de NULL
            while(busca->getFilha(busca->getPosOcupadas() - count) == NULL && count <= busca->getPosOcupadas()){
                count++;
            }
            busca = busca->getFilha(busca->getPosOcupadas() - count);//vai para o ultimo filho
        }
    }
    delete raiz;
}

//Retorna a ordem da arvore
int arvoreb::getOrdem(){
    return this->ordem;
}

//Busca uma chave na arvore(T:existe/ F:nao existe na arvore)
bool arvoreb::buscaChave(int chave, int* comparacoes, int* trocas){
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
    pagina* busca = raiz;*trocas = *trocas + 1;
    int posOcupadas;// Armazena a qtde de chaves armazenadas
    int count;// Variavel para percorrer o vetor de chaves de cada pagina
    *comparacoes = *comparacoes + 1;
    while(busca != NULL){*comparacoes = *comparacoes + 1;
        *comparacoes = *comparacoes + 1;
        if(busca->getPosOcupadas() == 0){//Se a pagina estiver vazia pare a verificacao
            break;
        }
        posOcupadas = busca->getPosOcupadas();*trocas = *trocas + 1;
        count = 0;// Reseta o contador para a proxima pagina
        //Percorre a pagina e verifica se a chave eh maior que o chaves->valor
        *comparacoes = *comparacoes + 1;
        while(count < posOcupadas && movie->getValor() > busca->getChave(count)->getValor()){
            count ++;*comparacoes = *comparacoes + 1;
            //Sai quando chegar ao fim ou se chegar em uma chave maior que a movie.Valor
        }
        
        //procura no filho que está no count
        //Se for nulo chegou na folha e devemos inserir
        *comparacoes = *comparacoes + 1;
        if(busca->getFilha(count)==NULL){
            break;
        }
        busca = busca->getFilha(count); *trocas = *trocas + 1;
        
    }
    busca->inserirNaFolha(movie, comparacoes, trocas);
    //Enquanto tiver paginas lotadas divida
    *comparacoes = *comparacoes + 1;cout << "qwe" << endl;//tirar que muda o erro
    cout << ":::" << (busca->getPosOcupadas() > 2*this->getOrdem()) << endl; 
    cout << busca->getPosOcupadas() << ": " << 2*this->getOrdem() << endl;
    while(busca->getPosOcupadas() > 2*this->getOrdem()){
        
        cout << "wwwww";
        *comparacoes = *comparacoes + 1;
        busca->splitPagina(comparacoes, trocas);
        busca = busca->getPai();
        *trocas = *trocas + 1;
    }
    cout << "teste"<< endl;
}