#include "arvoreB/arvoreb.h"
#include "arvoreB/chave.h"
#include "arvoreB/pagina.h"
#include "tela.h"
#include <fstream>//Manipulacao de arquivos
#include "stdio.h"
#include "stdlib.h"


using namespace std;

//funcao chamada no main para gerar a chave. Antes da criacao da chave (movie)
float calculaChave(int userId, int movieId){

    return (userId*movieId)/2;
}

//Le e fecha o arquivo de entrada
int* tela::lerEntrada(){
    //Analisando arquivo de entrada
    ifstream entrada;
    entrada.open("entrada.txt");
    int tam_entrada;
    string ent;
    getline(entrada, ent, '\n');
    tam_entrada = atoi(ent.c_str());
    int *entradas = new int[tam_entrada];
        
    if(entrada.is_open()){
        
        for(int i = 0; i<tam_entrada; i++){

            getline(entrada, ent, '\n');
            entradas[i] = atoi(ent.c_str());
        }

    }
    entrada.close();
    return entradas;
}

//leitura do ratings para arvoreB
void tela::leituraRatingsB(int* entradas, int menu){

//leitura e insercao na arvoreB

}

//leitura do ratings para arvoreVP
void tela::leituraRatingsVP(int* entradas){

//leitura e insercao na arvoreVP

}

//leitura do metadata
void tela::leituraOverview(int* entradas, int menu){

}


//Inicia o menu
void tela::exibeMenu(){
    int* entradas = lerEntrada();
    int menu = 1;//variavel para controle do menu
    int tamanhoEntrada = sizeof(entradas) / sizeof(entradas[0]);//tamanho da entrada

    while(menu != 0){
        cout << "1: Executar arvoreB d=3" << endl;
        cout << "2: Executar arvoreB d=8" << endl;
        cout << "3: Executar arvoreB d=17" << endl;
        cout << "4: Executar arvoreB d=30" << endl;
        cout << "5: Executar arvoreVP" << endl;
        cout << "6: Compactar Huffman" << endl;
        cout << "7: Compactar LZW" << endl;
        cout << "0: Sair"<< endl;

        cin >> menu;
        switch (menu)
        {
        case 1: case 2: case 3: case 4: 
            this->leituraRatingsB(entradas, menu);
            break;
        case 5:
            this->leituraRatingsVP(entradas);
            break;
        case 6: case 7:
            this->leituraOverview(entradas, menu);
            break;
        case 0:
            break;
        default:
            cout << "Numero invalido!" << endl;
        }
    }
}