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

}

//Destrutor padrao
arvorehf::~arvorehf(){

}

//Monta a arvore de huffman para o texto
void arvorehf::montarArvore(string texto){

    //Converte string em char[]
    char text[texto.size()]; 
    strcpy(text,texto.c_str());
    for(int i = 0; i < texto.size(); i++){
        for(int j = 0; j < this->arvore.size(); j++){
            if(text[i] == this->arvore[j].getCaractere){

            }
        }
    } 

}

//Codifica o texto usando a arvore de huffman
int* arvorehf::codifica(string texto){
    
    
}

//Decodifica um texto binario
string arvorehf::decodifica(string texto){

}