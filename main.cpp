#include <iostream>
#include <fstream>
#include "include/movies.h"
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//ANALISAR QUAL BIBLIOTECA A GENTE PODE REMOVER, PQ SAO MUITAS

#define NINT 100 //DEFINE O TAMANHO DO VETOR DE INTEIROS A SER ORDENADO

//#define N 100 //DEFINE O TAMANHO DO VETOR DE MOVIES A SER ORDENADO

int trocasDeRegistroINT = 0; //CONTADOR DAS TROCAS DE REGISTRO DO VETOR DE INTEIROS
int comparacoesINT = 0; //CONTADOR DAS COMPARACOES DO VETOR DE INTEIROS
int trocasDeRegistroMOV = 0; //CONTADOR DAS TROCAS DE REGISTRO DO VETOR DE MOVIES
int comparacoesMOV = 0; //CONTADOR DAS TROCAS DE REGISTRO DO VETOR DE MOVIES

using namespace std;

//-------------------------------------------------------
//QUICKSORT PRA UM VETOR DE INTEIROS

void trocaDePosicao (int i, int j, int *vet)
{
    int k = vet[i];
    vet[i] = vet[j];
    vet[j] = k;
    trocasDeRegistroINT++;
}

int particao(int start, int end, int *vet)
{
    int i = start;
    for (int j = start; j < end; j++)
    {

        if (vet[j] <= vet[end])
        {
            trocaDePosicao(i++, j, vet);
        }
        comparacoesINT++;
    }

    trocaDePosicao(i, end, vet);

    return i;
}

void quicksort (int start, int end, int *vet)
{
    if (start >= end)
        return;

    int pivo = particao(start, end, vet);

    quicksort(start, pivo - 1, vet);
    quicksort(pivo + 1, end, vet);
}

//-------------------------------------------------------
//QUICKSORT PRO VETOR MOVIES

void trocaDePosicaoMovies(int i, int j, movies *vet)
{
    int k = vet[i].movieid;
    vet[i].movieid = vet[j].movieid;
    vet[j].movieid = k;
    trocasDeRegistroMOV++;

}

int particaoMovies(int start, int end, movies *vet)
{
    int i = start;
    for (int j = start; j < end; j++)
    {

        if (vet[j].movieid <= vet[end].movieid)
        {
            trocaDePosicaoMovies(i++, j, vet);
        }
        comparacoesMOV++;
    }

    trocaDePosicaoMovies(i, end, vet);

    return i;
}

void quicksortM(int start, int end, movies *vet)
{
    if (start >= end)
        return;

    int pivo = particaoMovies(start, end, vet);

    quicksortM(start, pivo - 1, vet);
    quicksortM(pivo + 1, end, vet);
}
//-------------------------------------------------------

int main()
{

    //PARTE DE CODIGO RELATIVA A LEITURA E ORDENACAO DE UM VETOR DE INTEIROS
    /*
    int *v = new int[NINT];
    srand(time(NULL));
    for(int i = 0; i<NINT; i++)
    {
        v[i] = rand()%1000;
    }
    int y = 0;

    cout<<"IMPRIMINDO VETOR DE INTEIROS"<<endl;
    for(int i = 0; i < NINT; i++)
    {
        cout<<v[i]<<" - ";
        y++;
        if(y>=10)
        {
            y = 0;
            cout<<endl;
        }
    }
    trocasDeRegistroINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
    comparacoesINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
    quicksort(0, N-1, v);
    y=0;
    cout<<endl<<endl;
    cout<<"IMPRIMINDO VETOR DE INTEIROS ORDENADO"<<endl;
    for(int i = 0; i<NINT; i++)
    {
        cout<<v[i]<<" - ";
        y++;
        if(y>=10)
        {
            y = 0;
            cout<<endl;
        }
    }
        cout<<endl<<endl<<"numero de comparacoes: " << comparacoesINT<<endl;
        cout<<"numero de trocas de registro: " << trocasDeRegistroINT<< endl;
        //!!!!!NAO IMPLEMENTAMOS MEDIDOR DE TEMPO AQUI!!!!!!!
*/
    //--------------------------------------------------

    //CODIGO RELATIVO A LEITURA E ORDENACAO DOS DADOS DO ARQUIVO MOVIES

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
    int aleatorio;//variável que irá receber o valor aleatorio
    ifstream arq;
    for(int j =1; j<=5; j++){//Executar 5 vezes para cada N

        srand(5*j);
        
        arq.open("DAVI REZENDE DOMINGUES - ratings_small.csv");

        if(arq.is_open())
        {   
            int N;
            movies *vetor = new movies[entradas[0]];
            movies m;
            std::string s;
            //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
            getline(arq, s, ',');
            getline(arq, s, ',');
            getline(arq, s, ',');
            getline(arq, s, '\n');
            //--------------------------
                N = entradas[0];
            //LENDO O ARQUIVO----------------------
            for(int i = 0; i < N; i++)
            {   aleatorio = rand()%10;
                if(aleatorio==1){
                    getline(arq, s, ',');
                    m.userid = atoi(s.c_str());

                    getline(arq, s, ',');
                    m.movieid = atoi(s.c_str());

                    getline(arq, s, ',');
                    m.rating = atof(s.c_str());

                    getline(arq, s, '\n');
                    m.timestamp = atol(s.c_str());

                    vetor[i] = m;
                }
            }
            //------------------------------------
            /*
            //IMPRIMINDO O ARQUIVO DE FORMA DESORDENADA
            cout<<endl<<endl;
            cout<<"IMPRIMINDO VETOR DE FILMES"<<endl;
            for(int i = 0; i < N; i++)
            {
                cout<<"USER ID: "<<vetor[i].userid<<endl;
                cout<<"MOVIE ID: "<<vetor[i].movieid<<endl;
                cout<<"RATING: "<<vetor[i].rating<<endl;
                cout<<"TIMESTAMPS: "<<vetor[i].timestamp<<endl;
            }
            */
            //------------------------------------

            //APLICANDO O QUICKSORT
            clock_t fim, inicio;
            inicio = clock();
            trocasDeRegistroMOV = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
            comparacoesMOV = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT

            quicksortM(0, 99, vetor);

            fim = clock();
            //--------------------

            /*
            //IMPRIMINDO VETOR ORDENADO E SUAS ESTATISTICAS
            cout<<endl<<endl;
            cout<<"IMPRIMINDO VETOR ORDENADO POR MovieId DE FILMES"<<endl;
            for(int i = 0; i < N; i++)
            {
                cout<<"USER ID: "<<vetor[i].userid<<endl;
                cout<<"MOVIE ID: "<<vetor[i].movieid<<endl;
                cout<<"RATING: "<<vetor[i].rating<<endl;
                cout<<"TIMESTAMPS: "<<vetor[i].timestamp<<endl;
            }
            */
            cout<<endl<<endl<<"numero de comparacoes: " << comparacoesMOV<<endl;
            cout<<"numero de trocas de registro: " << trocasDeRegistroMOV<< endl;
            cout<<"tempo de execucao: "<< ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000 << "ms"<<endl << endl;
            //------------------------------------------
            delete []vetor;//Deletando vetor de movies

            arq.close();//FECHANDO O ARQUIVO
        }
        //----------------------------------------------------------------------
    }//Fim da 5 execução de cada N





    return 0;
}
