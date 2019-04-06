#include <iostream>
#include <fstream>
#include "movies.h"
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

//ANALISAR QUAL BIBLIOTECA A GENTE PODE REMOVER, PQ SAO MUITAS

#define N 100 //DEFINE O TAMANHO DO VETOR DE INTEIROS A SER ORDENADO

int trocasDeRegistroINT = 0; //CONTADOR DAS TROCAS DE REGISTRO DO VETOR DE INTEIROS
int comparacoesINT = 0; //CONTADOR DAS COMPARACOES DO VETOR DE INTEIROS
int trocasDeRegistroMOV = 0; //CONTADOR DAS TROCAS DE REGISTRO DO VETOR DE MOVIES
int comparacoesMOV = 0; //CONTADOR DAS TROCAS DE REGISTRO DO VETOR DE MOVIES

using namespace std;

//-------------------------------------------------------
//QUICKSORT PRA UM VETOR DE INTEIROS

void swap (int i, int j, int *vet)
{
    int k = vet[i];
    vet[i] = vet[j];
    vet[j] = k;
}

int partition (int start, int end, int *vet)
{
    int i = start;
    for (int j = start; j < end; j++)
    {

        if (vet[j] <= vet[end])
        {
            swap(i++, j, vet);
        }
    }

    swap(i, end, vet);

    return i;
}

void quicksort (int start, int end, int *vet)
{
    if (start >= end)
        return;

    int pivot = partition(start, end, vet);

    quicksort(start, pivot - 1, vet);
    quicksort(pivot + 1, end, vet);
}

//-------------------------------------------------------
//QUICKSORT PRO VETOR MOVIES

void swapM(int i, int j, movies *vet)
{
    int k = vet[i].movieid;
    vet[i].movieid = vet[j].movieid;
    vet[j].movieid = k;

}

int partitionM(int start, int end, movies *vet)
{
    int i = start;
    for (int j = start; j < end; j++)
    {

        if (vet[j].movieid <= vet[end].movieid)
        {
            swapM(i++, j, vet);
        }
    }

    swapM(i, end, vet);

    return i;
}

void quicksortM(int start, int end, movies *vet)
{
    if (start >= end)
        return;

    int pivot = partitionM(start, end, vet);

    quicksortM(start, pivot - 1, vet);
    quicksortM(pivot + 1, end, vet);
}
//-------------------------------------------------------

int main()
{
    /*
    int *v = new int[N];
    srand(time(NULL));
    for(int i = 0; i<N; i++)
    {
        v[i] = rand()%1000;
    }
    int y = 0;

    cout<<"IMPRIMINDO VETOR DE INTEIROS"<<endl;
    for(int i = 0; i < N; i++)
    {
        cout<<v[i]<<" - ";
        y++;
        if(y>=10)
        {
            y = 0;
            cout<<endl;
        }
    }

    quicksort(0, N-1, v);
    y=0;
    cout<<endl<<endl;
    cout<<"IMPRIMINDO VETOR DE INTEIROS ORDENADO"<<endl;
    for(int i = 0; i<N; i++)
    {
        cout<<v[i]<<" - ";
        y++;
        if(y>=10)
        {
            y = 0;
            cout<<endl;
        }
    }
*/
    ifstream arq;
    arq.open("DAVI REZENDE DOMINGUES - ratings_small.csv");

    if(arq.is_open())
    {
        movies *vetor = new movies[100];
        movies m;
        std::string s;

        //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
        getline(arq, s, ',');
        getline(arq, s, ',');
        getline(arq, s, ',');
        getline(arq, s, '\n');
        //--------------------------

        for(int i = 0; i < 100; i++)
        {
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
        cout<<endl<<endl;
        cout<<"IMPRIMINDO VETOR DE FILMES"<<endl;
        for(int i = 0; i < 100; i++)
        {
            cout<<"USER ID: "<<vetor[i].userid<<endl;
            cout<<"MOVIE ID: "<<vetor[i].movieid<<endl;
            cout<<"RATING: "<<vetor[i].rating<<endl;
            cout<<"TIMESTAMPS: "<<vetor[i].timestamp<<endl;
        }
        clock_t fim, inicio;
        inicio = clock();
        quicksortM(0, 99, vetor);
        fim = clock();
        cout<<endl<<endl;
        cout<<"IMPRIMINDO VETOR ORDENADO POR MovieId DE FILMES"<<endl;
        for(int i = 0; i < 100; i++)
        {
            cout<<"USER ID: "<<vetor[i].userid<<endl;
            cout<<"MOVIE ID: "<<vetor[i].movieid<<endl;
            cout<<"RATING: "<<vetor[i].rating<<endl;
            cout<<"TIMESTAMPS: "<<vetor[i].timestamp<<endl;
        }

        cout<<endl<<endl<<"tempo de execucao: "<< (fim - inicio)<<endl;

        //system("pause");

        arq.close();
    }

    return 0;
}
