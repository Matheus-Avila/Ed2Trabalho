#include <fstream>//Manipulacao de arquivos
#include <time.h>
#include "stdio.h"
#include "stdlib.h"
#include "tela.h"
#include "arvores/arvoreB/arvoreb.h"
#include "arvores/arvoreB/chave.h"
#include "arvores/arvoreB/pagina.h"
#include "arvores/arvoreVP/no.h"
#include "arvores/arvoreVP/arvoreVP.h"
#include "compressao/huffman/arvorehf.h"
#include "compressao/huffman/nohf.h"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;


tela::tela(){

}


tela::~tela(){

}

//funcao chamada no main para gerar a chave. Antes da criacao da chave (movie)
int tela::calculaChave(int userId, int movieId){

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

    int tamanhoEntrada = sizeof(entradas) / sizeof(entradas[0]);//tamanho do vetor entradas
    
    fstream saidaB;
    saidaB.open("arvoresbInsersao.txt", std::ios::app);//Abre arquivo para escrever no final
    fstream saidaB2;
    saidaB2.open("arvoresbBusca.txt", std::ios::app);//Abre arquivo para escrever no final

    //Variaveis que vao armazenar as estatisticas na insersao
    int estatisticasNumComparacoes[5] = {0,0,0,0,0};
    int estatisticasNumTrocas[5] = {0,0,0,0,0};
    float estatisticasTempo[5] = {0,0,0,0,0};
    clock_t fim, inicio;

    //Variaveis que vao armazenar as estatistica na busca
    int estatisticasNumCompBusca[5] = {0,0,0,0,0};
    int estatisticasNumTrocasBusca[5] = {0,0,0,0,0};
    int estatisticasTempoBusca[5] = {0,0,0,0,0};
    
    //Leitura do arquivo rating
    int aleatorio;//variável que irá receber o valor aleatorio

    switch (menu)
    {
    case 1:
        saidaB << "Resultados para arvoreB d : 3 " << endl;
        saidaB2 << "Resultados para arvoreB d : 3 " << endl;
        break;
    case 2:
        saidaB << "Resultados para arvoreB d : 8 " << endl;
        saidaB2 << "Resultados para arvoreB d : 8 " << endl;
        break;
    case 3:
        saidaB << "Resultados para arvoreB d : 17 " << endl;
        saidaB2 << "Resultados para arvoreB d : 17 " << endl;
        break;
    case 4:
        saidaB << "Resultados para arvoreB d : 30 " << endl;
        saidaB2 << "Resultados para arvoreB d : 30 " << endl;
        break;
    }

    ifstream arq;
    for(int i = 0; i < 6; i++){
        
        saidaB << endl << "Resultado da arvore B para N = " << entradas[i]  << endl << endl;

        saidaB2 << endl << "Resultado da arvore B para N = " << entradas[i]  << endl << endl;
        for(int j = 1; j <= 5; j++){//Executar 5 vezes para cada N
            
            srand(2*j*i);//Sementes diferentes para cada execução de cada N

            arq.open("ratings.csv");
            
            arvoreb* arvore;

            int tam = entradas[i];

            if(arq.is_open())
            {
                switch (menu)//Define a ordem da arvore
                {
                case 1:
                    arvore = new arvoreb(3);
                    break;
                case 2:
                    arvore = new arvoreb(8);
                    break;
                case 3:
                    arvore = new arvoreb(17);
                    break;
                case 4:
                    arvore = new arvoreb(30);
                    break;
                }cout << "lendo arquivo" << endl;
                std::string s;
                //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
                getline(arq, s, '\n');
                //Variaveis auxiliares
                int userid, movieid, chaveint, timestamp, rating;
                //LENDO O ARQUIVO----------------------
                inicio = clock();
                for(int i = 0; i < tam; i++)
                {   
                    aleatorio = rand()%2;
                    if(aleatorio==1){
                        getline(arq, s, ',');
                        userid = atoi(s.c_str());

                        getline(arq, s, ',');
                        movieid = atoi(s.c_str());
                        
                        chaveint = calculaChave(userid, movieid);
                        
                        getline(arq, s, ',');
                        rating = atof(s.c_str());

                        getline(arq, s, '\n');
                        timestamp = atol(s.c_str());cout << "I";
                        //Se a chave ja existir
                        if(arvore->buscaChave(chaveint, &arvore->numeroComparacoes, &arvore->numeroTrocas)){
                            i--;    
                        }else{
                            chave *movie = new chave(chaveint, rating, timestamp);
                            
                            arvore->inserirChave(movie, &arvore->numeroComparacoes, &arvore->numeroTrocas);
                        }
                        
                    }else{
                        i--;
                    }
                }//Fim das insersoes
                fim = clock();
            }
            //Armazenar dados no vetor
            estatisticasNumComparacoes[j-1] = arvore->numeroComparacoes;
            estatisticasNumTrocas[j-1] = arvore->numeroTrocas;
            estatisticasTempo[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
            
            //Zera os valores das estatisticas para serem usados pela busca

            arvore->numeroComparacoes = 0;
            arvore->numeroTrocas = 0;

            //Executa a busca tam vezes---------------
            //Numeros aleatorios para fazer a busca
            int numRand1, numRand2, randChave;
            inicio = clock();
            for(int i = 0; i < tam ; i++){
                numRand1 = rand()%20;
                numRand2 = rand()%99 + 400;
                randChave = calculaChave(numRand1, numRand2);
                arvore->buscaChave(randChave, &arvore->numeroComparacoes, &arvore->numeroTrocas);
            }
            fim = clock();
            estatisticasNumCompBusca[j-1] = arvore->numeroComparacoes;
            estatisticasNumTrocasBusca[j-1] = arvore->numeroTrocas;
            estatisticasTempoBusca[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
            //deletar arvore
            delete arvore;
            arvore = NULL;
            arq.close();
        }//Fim da 5 execucao para cada N

        //Análise dos dados para cada N

        //Análise para a insersao
        float auxComp = 0;
        float auxTroca = 0;
        float auxTempo = 0;
        for(int i = 0; i < 5; i++){
            auxComp+=estatisticasNumComparacoes[i];
            auxTroca+=estatisticasNumTrocas[i];
            auxTempo+=estatisticasTempo[i];
        }
        auxComp = auxComp/5.0;
        auxTroca = auxTroca/5.0;
        auxTempo = (float) (auxTempo/5);
        saidaB << endl << "Média do número de comparações: " << auxComp << endl;
        saidaB << "Média do número de trocas: " << auxTroca << endl;
        saidaB << "Média do tempo de execução: " << auxTempo << "ms" << endl << endl;

        //Análise para a busca
        float auxCompBusca = 0;
        float auxTrocaBusca = 0;
        float auxTempoBusca = 0;
        for(int i = 0; i < 5; i++){
            auxCompBusca+=estatisticasNumCompBusca[i];
            auxTrocaBusca+=estatisticasNumTrocasBusca[i];
            auxTempoBusca+=estatisticasTempoBusca[i];
        }
        auxCompBusca = auxCompBusca/5.0;
        auxTrocaBusca = auxTrocaBusca/5.0;
        auxTempoBusca = (float) (auxTempoBusca/5);
        saidaB2 << endl << "Média do número de comparações: " << auxCompBusca << endl;
        saidaB2 << "Média do número de trocas: " << auxTrocaBusca << endl;
        saidaB2 << "Média do tempo de execução: " << auxTempoBusca << "ms" << endl << endl;

    }//Fim das execucoes para todos os valores 
    saidaB.close();
    saidaB2.close();
    cout << "Executado com sucesso!!!" << endl << endl;
}

//leitura do ratings para arvoreVP
void tela::leituraRatingsVP(int* entradas){

    int tamanhoEntrada = sizeof(entradas) / sizeof(entradas[0]);//tamanho do vetor entradas
    
    fstream saidaVP;
    saidaVP.open("arvoresVP.txt", std::ios::app);//Abre arquivo para escrever no final
    fstream saidaVP2;
    saidaVP.open("arvoresVPBusca.txt", std::ios::app);//Abre arquivo para escrever no final

    //Variaveis que vao armazenar as estatisticas na insersao
    int estatisticasNumComparacoes[5] = {0,0,0,0,0};
    int estatisticasNumTrocas[5] = {0,0,0,0,0};
    float estatisticasTempo[5] = {0,0,0,0,0};
    clock_t fim, inicio;

    //Variaveis que vao armazenar as estatistica na busca
    int estatisticasNumCompBusca[5] = {0,0,0,0,0};
    int estatisticasNumTrocasBusca[5] = {0,0,0,0,0};
    int estatisticasTempoBusca[5] = {0,0,0,0,0};
    
    //Leitura do arquivo rating
    int aleatorio;//variável que irá receber o valor aleatorio
    
    ifstream arq;
    for(int i = 0; i < tamanhoEntrada; i++){
        
        saidaVP << endl << "Resultado da ordenação para N = " << entradas[i]  << endl << endl;
        for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
            
            srand(2*j*i);//Sementes diferentes para cada execução de cada N

            arvoreVP* arvore = new arvoreVP();
            
            int tam = entradas[i];

            arq.open("ratings.csv");

            if(arq.is_open())
            {   
                
                std::string s;
                //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
                getline(arq, s, '\n');
                int userid, movieid, chaveint, timestamp, rating;
                //LENDO O ARQUIVO----------------------
                inicio = clock();
                for(int i = 0; i < tam ; i++)
                {   
                    aleatorio = rand()%2;
                    if(aleatorio==1){
                        getline(arq, s, ',');
                        userid = atoi(s.c_str());

                        getline(arq, s, ',');
                        movieid = atoi(s.c_str());
                        
                        chaveint = calculaChave(userid, movieid);
                        
                        getline(arq, s, ',');
                        rating = atof(s.c_str());

                        getline(arq, s, '\n');
                        timestamp = atol(s.c_str());
                        
                        if(arvore->buscarValor(chaveint)){//Se a chave ja existir
                            i--;
                        }else{
                            no *movie = new no(chaveint, rating, timestamp);
                            arvore->inserirValor(movie, &arvore->numeroComparacoes, &arvore->numeroTrocas);
                        }
                    }else{
                        i--;
                    }
                }//Fim das insersoes
                fim = clock();
            }
            //Armazenar dados no vetor
            estatisticasNumComparacoes[j-1] = arvore->numeroComparacoes;
            estatisticasNumTrocas[j-1] = arvore->numeroTrocas;
            estatisticasTempo[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
            
            //Zera os valores das estatisticas para serem usados pela busca

            arvore->numeroComparacoes = 0;
            arvore->numeroTrocas = 0;
            
            //Executa a busca tam vezes---------------
            //Numeros aleatorios para fazer a busca
            int numRand1, numRand2, randChave;
            inicio = clock();
            for(int i = 0; i < tam ; i++){
                numRand1 = rand()%20;
                numRand2 = rand()%99 + 400;
                randChave = calculaChave(numRand1, numRand2);
                arvore->buscarValor(randChave);
            }
            fim = clock();
            estatisticasNumCompBusca[j-1] = arvore->numeroComparacoes;
            estatisticasNumTrocasBusca[j-1] = arvore->numeroTrocas;
            estatisticasTempoBusca[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
            
            //deletar arvore
            delete arvore;
            arq.close();
        }//Fim da 5 execucao para cada N

        //Análise dos dados para cada N
        float auxComp = 0;
        float auxTroca = 0;
        float auxTempo = 0;
        for(int i = 0; i < 5; i++){
            auxComp+=estatisticasNumComparacoes[i];
            auxTroca+=estatisticasNumTrocas[i];
            auxTempo+=estatisticasTempo[i];
        }
        auxComp = auxComp/5.0;
        auxTroca = auxTroca/5.0;
        auxTempo = (float) (auxTempo/5);
        saidaVP << endl << "Média do número de comparações: " << auxComp << endl;
        saidaVP << "Média do número de trocas: " << auxTroca << endl;
        saidaVP << "Média do tempo de execução: " << auxTempo << "ms" << endl << endl;

        //Análise para a busca
        float auxCompBusca = 0;
        float auxTrocaBusca = 0;
        float auxTempoBusca = 0;
        for(int i = 0; i < 5; i++){
            auxCompBusca+=estatisticasNumCompBusca[i];
            auxTrocaBusca+=estatisticasNumTrocasBusca[i];
            auxTempoBusca+=estatisticasTempoBusca[i];
        }
        auxCompBusca = auxCompBusca/5.0;
        auxTrocaBusca = auxTrocaBusca/5.0;
        auxTempoBusca = (float) (auxTempoBusca/5);
        saidaVP2 << endl << "Média do número de comparações: " << auxCompBusca << endl;
        saidaVP2 << "Média do número de trocas: " << auxTrocaBusca << endl;
        saidaVP2 << "Média do tempo de execução: " << auxTempoBusca << "ms" << endl << endl;

    }//Fim das execucoes para todos os valores 

    saidaVP.close();
    saidaVP2.close();
    cout << "Executado com sucesso!!!" << endl << endl;
}

//leitura do metadata
void tela::leituraOverview(int* entradas, int menu){

    string s;
    cout << "Digite a string:" << endl;
    cin >> s;
    arvorehf* arvore = new arvorehf();
    arvore->montarArvore(s);
    vector<int> vetor = arvore->codifica(s);
    
    std::ostringstream StringRepresentation;
    for ( vector<int>::iterator it = vetor.begin(); it != vetor.end(); it++ ) {
        StringRepresentation << *it << " ";
    }

    const char * CharArray = StringRepresentation.str().c_str();

    cout << CharArray;
}


//Inicia o menu
void tela::exibeMenu(){
    int* entradas = lerEntrada();
    int menu = 1;//variavel para controle do menu
    int tamanhoEntrada = sizeof(entradas) / sizeof(entradas[0]);//tamanho do vetor entradas

    while(menu != 0){
        cout << endl << "1: Executar arvoreB d=3" << endl;
        cout << "2: Executar arvoreB d=8" << endl;
        cout << "3: Executar arvoreB d=17" << endl;
        cout << "4: Executar arvoreB d=30" << endl;
        cout << "5: Executar arvoreVP" << endl;
        cout << "6: Compactar por Huffman" << endl;
        cout << "7: Compactar por LZW" << endl;
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