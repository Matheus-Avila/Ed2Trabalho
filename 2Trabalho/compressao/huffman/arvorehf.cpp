#include "arvorehf.h"
#include "stdio.h"
#include "stdlib.h"
#include "nohf.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

//Construtor padrao
arvorehf::arvorehf(){
    this->size = 0;
}

//Destrutor padrao
arvorehf::~arvorehf(){

}

//Monta a arvore de huffman para o texto
void arvorehf::montarArvore(string texto){

    //Converte string em char[]
    char text[texto.size()]; 
    strcpy(text,texto.c_str());
    
    //Le o texto e armazena as frequencias
    int j;//Indice da tabela que tambem eh usado para verificar se o caractere nao esta na tabela
    for(int i = 0; i < texto.size(); i++){
        for(j = 0; j < this->arvoreTabela.size(); j++){
            //Se o caractere existe na tabela aumenta a frequencia e termina o for interno
            if(text[i] == this->arvoreTabela[j].getCaractere){
                this->arvoreTabela[j].addFrequencia();
                break;
            }
        }
        if(j == this->arvoreTabela.size()){//text[i] deve ser inserido na arvoreTabela
            this->arvoreTabela.push_back(text[i]);
        }
        
    } 
    
    //Monta a arvore de huffman na tabela de frequencias dos caracteres
    
    this->size = this->arvoreTabela.size();
    
    //menor1 <= menor2
    int menor1 = -1, menor2 = -1, j;
    
    nohf novo;//no que sera criado a cada iteracao do for externo
        
    for(int i = 0; i < this->size; i++){//Repete n-1 vezes, onde n eh o numero de caracteres distintos
        
        //O for interno faz j == size mas size cresce apos terminar o for interno
        //Tratando para nao pegarmos os mesmos indices nas outras iteracoes
        if(j == this->arvoreTabela.size()-1){
            
            menor1 = -1;
            menor2 = -1;
        }
        
        //Procura na tabela os menores(o tamanho pode, e deve aumentar em cada iteracao)
        for(j = 0; j < this->arvoreTabela.size(); j++){
            //Se nao tem pai eh um candidato a ser unido
            if(!this->arvoreTabela[j].temPai()){

                //Se estiver no inicio da busca o 1 candidato eh menor1 e menor2
                if(menor1 == -1){
                    menor1 = j;
                }
                if(menor2 == -1){
                    menor2 = j;
                }
                
                //Se o elemento tem frequencia menor que menor1
                if(this->arvoreTabela[j].getFrequencia() <
                 this->arvoreTabela[menor1].getFrequencia()){
                    menor2 = menor1;
                    menor1 = j;
                }
                else{
                //Se o elemento tem frequencia menor que menor2
                    if(this->arvoreTabela[j].getFrequencia() <
                 this->arvoreTabela[menor2].getFrequencia()){
                    menor2 = j;
                    }
                }
            }
        }//Fim da busca pelos caracteres com menor frequencia para cada iteracao
        //adiciona o novo no na arvoreTabela
        novo.setFrequencia(this->arvoreTabela[menor1].getFrequencia()+
        this->arvoreTabela[menor2].getFrequencia());
        novo.setFilhoEsq(menor1);//A menor frequencia fica na esquerda
        novo.setFilhoDir(menor2);
        novo.setPai(-1);//Novo nao tem pai
        this->arvoreTabela[menor1].setPai(this->arvoreTabela.size());
        this->arvoreTabela[menor2].setPai(this->arvoreTabela.size());
        this->arvoreTabela.push_back(novo);//Aumenta arvoreTabela.size()
    }
    //Arvore montada
    //As folhas serao os primeiros size elementos da arvoreTabela
}

//Codifica o texto usando a arvore de huffman
vector<int> arvorehf::codifica(string texto){
    vector<int> temporario;//vector que armazena codigo invertido de cada caractere
    vector<int> codigo;//codigo final do texto
    int busca;//Indice que vai da folha ate a raiz
    int paiBusca;//Indice que indica o pai da busca
    //Converte string em char[]
    char text[texto.size()]; 
    strcpy(text,texto.c_str());
//A codificacao comeca nas folhas e termina na raiz
    for(int i = 0; i < texto.size(); i++){//Percorre o texto
        for(int j = 0; j < this->size; j++){//Percore as folhas da tabelaArvore
            //Achou a folha correspondente ao caractere text[i]
            if(text[i] == this->arvoreTabela[j].getCaractere()){
                busca = j;
                while(this->arvoreTabela[busca].temPai()){//Enquanto nao for a raiz
                    paiBusca = this->arvoreTabela[busca].getPai();
                    //Se busca for filho a esquerda insere 0 no codigo temporario
                    if(this->arvoreTabela[paiBusca].getFilhoEsq() == busca){
                        temporario.push_back(0);
                    }
                    else{
                        temporario.push_back(1);
                    }
                }
                break;//Achou o codigo, portanto pode parar de percorrer as folhas
            }
        }//Termino do laco pelas folhas
        //Tratamento do codigo temporario que esta invertido
        for(int i = 0; i < temporario.size(); i++){
            codigo.push_back(temporario.back());
            temporario.pop_back();
        }
        //Codigo possui o codigo correto do caractere
    }
    
}

//Decodifica um texto binario
string arvorehf::decodifica(string texto){

}