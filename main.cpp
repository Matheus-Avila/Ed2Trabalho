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
//--------------------Cenário 1 Funções ----------------------------

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

//--------------------Fim Cenário 1 Funções ----------------------------


//--------------------Cenário 2 Funções ----------------------------


//---------------------QuickSort Mediana 3----------------------

void trocaPosicao2(int A[], int i, int j){
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

int particiona2(int A[], int inicio, int fim) {

    srand(time(0));
    int indiceAleatorio[3];
    //Garantindo que os números aleatórios são diferentes
    for(int i = 0; i <= 2; i++){
        indiceAleatorio[i] = rand()%(fim-inicio);
        while(i==1 && indiceAleatorio[i]==indiceAleatorio[i-1]){
            indiceAleatorio[i] = rand()%(fim-inicio);
        }
        while(i==2 && (indiceAleatorio[i]==indiceAleatorio[i-1] || indiceAleatorio[i]==indiceAleatorio[i-2])){
            indiceAleatorio[i] = rand()%(fim-inicio);
        }
    }
    int meio = (inicio + fim) / 2;
    int a = A[indiceAleatorio[0]];
    int b = A[indiceAleatorio[1]];
    int c = A[indiceAleatorio[2]];
    int medianaIndice; //índice da mediana
    if (a < b) {
        if (b < c) {
            //a < b && b < c
            medianaIndice = meio;
        } else {
            if (a < c) {
                //a < c && c <= b
                medianaIndice = fim;
            } else {
                //c <= a && a < b
                medianaIndice = inicio;
            }
        }
    } else {
        if (c < b) {
            //c < b && b <= a
            medianaIndice = meio;
        } else {
            if (c < a) {
                //b <= c && c < a
                medianaIndice = fim;
            } else {
                //b <= a && a <= c
                medianaIndice = inicio;
            }
        }
    }
    //Coloca o elemento da mediana no fim para poder usar o Quicksort
    trocaPosicao2(A, medianaIndice, fim);
        
    //O pivo é o elemento final
    int pivo = A[fim];
    int i = inicio - 1;
    int j;
    //Passa os menores que o pivô para a partição da esquerda
    for (j = inicio; j <= fim - 1; j++) {
        if (A[j] <= pivo) {
            i = i + 1;
            trocaPosicao2(A, i, j);
        }
    }
    //Coloca o pivô na posição de ordenação
    trocaPosicao2(A, i + 1, fim);
    return i + 1; //Retorna a posição do pivô
}
void quicksortMedTres(int A[], int inicio, int fim) {
    if (inicio < fim) {
        int q = particiona2(A, inicio, fim);
        quicksortMedTres(A, inicio, q - 1);
        quicksortMedTres(A, q + 1, fim);
    }
}

//---------------QuickSort Mediana 5---------------

int particiona2Med5(int A[], int inicio, int fim) {

    srand(time(0));
    int indiceAleatorio[5]; // Vetor de indices aleatórios
    //Garantindo que os números aleatórios são diferentes
    for(int i = 0; i <= 4; i++){
        indiceAleatorio[i] = rand()%(fim-inicio);
        while(i==1 && indiceAleatorio[i]==indiceAleatorio[i-1]){
            indiceAleatorio[i] = rand()%(fim-inicio);
        }
        while(i==2 && (indiceAleatorio[i]==indiceAleatorio[i-1] || indiceAleatorio[i]==indiceAleatorio[i-2])){
            indiceAleatorio[i] = rand()%(fim-inicio);
        }
        while(i==3 && (indiceAleatorio[i]==indiceAleatorio[i-1] || indiceAleatorio[i]==indiceAleatorio[i-2]
         || indiceAleatorio[i]==indiceAleatorio[i-3])){
            indiceAleatorio[i] = rand()%(fim-inicio);
        }
        while(i==4 && (indiceAleatorio[i]==indiceAleatorio[i-1] || indiceAleatorio[i]==indiceAleatorio[i-2]
         || indiceAleatorio[i]==indiceAleatorio[i-3] || indiceAleatorio[i]==indiceAleatorio[i-4])){
            indiceAleatorio[i] = rand()%(fim-inicio);
        }
    }
    int aleatorio[5]; //Vetor com o valor dos índices aleatórios
    for(int i = 0; i <=4; i++){
        aleatorio[i] = A[indiceAleatorio[i]];
    }
    int medianaIndice;//índice da mediana, que será o pivô
    quicksort(0, 4, aleatorio);
    //procurando qual indice corresponde a mediana(aleatorio[2])
    for(int i =0; i <= 4; i++){
        if(aleatorio[2] == A[indiceAleatorio[i]]){
            medianaIndice = indiceAleatorio[i];
        }
    }
    
    //Coloca o elemento da mediana no fim para poder usar o Quicksort
    trocaPosicao2(A, medianaIndice, fim);
        
    //O pivo é o elemento final
    int pivo = A[fim];
    int i = inicio - 1;
    int j;
    //Passa os menores que o pivô para a partição da esquerda
    for (j = inicio; j <= fim - 1; j++) {
        if (A[j] <= pivo) {
            i = i + 1;
            trocaPosicao2(A, i, j);
        }
    }
    //Coloca o pivô na posição de ordenação
    trocaPosicao2(A, i + 1, fim);
    return i + 1; //Retorna a posição do pivô
}
void quicksortMedCinco(int A[], int inicio, int fim) {
    if (inicio < fim) {
        int q = particiona2Med5(A, inicio, fim);
        quicksortMedCinco(A, inicio, q - 1);
        quicksortMedCinco(A, q + 1, fim);
    }
}

//--------------InsertionSort------------------

void InsertionSort(int vet[], int tam){
    int j;
    int pivo;
    for(int i = 1; i<tam-1; i++){
        j= i-1;
        pivo = vet[i];
        for(j; j <= 0; j--){
            if(pivo<vet[j]){
                vet[j+1]= vet[j];
            }
            else{
                vet[j+1] = pivo;
            }
        }

    }
}


//-----------QuickSort Insertion m = 10--------------

void QuickInsertionSort10 (int start, int end, int *vet)
{
    if((end - start + 1 ) <= 10){
        InsertionSort(vet, (end - start + 1));
    }
    else{
        int pivo = particao(start, end, vet);

        QuickInsertionSort10(start, pivo - 1, vet);
        QuickInsertionSort10(pivo + 1, end, vet);
    }
}


//-----------QuickSort Insertion m = 100----------------

void QuickInsertionSort100 (int start, int end, int *vet)
{
    if((end - start + 1 ) <= 100){
        InsertionSort(vet, (end - start + 1));
    }
    else{
        int pivo = particao(start, end, vet);

        QuickInsertionSort100(start, pivo - 1, vet);
        QuickInsertionSort100(pivo + 1, end, vet);
    }
}

//--------------------Fim Cenário 2 Funções ----------------------------

//--------------------Cenário 3 Funções ----------------------------

int main()
{   

    //--------------------Cenário 1 Main ----------------------------

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

    int estatisticaComparacoesMOV[5] = {0,0,0,0,0};
    int estatisticaTrocasMOV[5] = {0,0,0,0,0};
    float estatisticaTempoMOV[5] = {0,0,0,0,0};
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


    fstream saida1;
    saida1.open("cenario1.txt");
    saida1 << "Resultado da ordenação do vetor de movies" << endl << endl;

    //Leitura do arquivo rating
    int aleatorio;//variável que irá receber o valor aleatorio
    int c = 0;//auxiliar
    ifstream arq;
    for(int i = 0; i< tam_entrada; i++){
        saida1 << endl << "Resultado da ordenação para N = " << entradas[i]  << endl << endl;
        for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
            cout << endl << j << " execução para N = " << entradas[i];
            srand(2*j*i);//Sementes diferentes para cada execução de cada N

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
                    c++;//auxiliar
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
                    }else{
                        i--;
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
                estatisticaComparacoesMOV[j-1] = comparacoesMOV;
                estatisticaTrocasMOV[j-1] = trocasDeRegistroMOV;
                estatisticaTempoMOV[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
                cout<<endl<<endl<<"numero de comparacoes: " << comparacoesMOV<<endl;
                cout<<"numero de trocas de registro: " << trocasDeRegistroMOV<< endl;
                cout<<"tempo de execucao: "<< ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000 <<
                "ms"<<c<<endl << endl;
                //------------------------------------------
                delete []vetor;//Deletando vetor de movies

                arq.close();//FECHANDO O ARQUIVO DE DADOS
            }
            
        }//Fim da 5 execução de cada N
        cout << "--------------------------------------" << endl;
        //Análise dos dados para cada N
        int auxCompMov = 0;
        int auxTrocaMov = 0;
        float auxTempoMov = 0;
        for(int i = 0; i < 5; i++){
            auxCompMov+=estatisticaComparacoesMOV[i];
            auxTrocaMov+=estatisticaTrocasMOV[i];
            auxTempoMov+=estatisticaTempoMOV[i];
        }
        auxCompMov = auxCompMov/5;
        auxTrocaMov = auxTrocaMov/5;
        auxTempoMov = (float) (auxTempoMov/5);
        saida1 << endl << "Média do número de comparações: " << auxCompMov << endl;
        saida1 << "Média do número de trocas: " << auxTrocaMov << endl;
        saida1 << "Média do tempo de execução: " << auxTempoMov << "ms" << endl << endl;

    }//Fim das N execuções
    saida1.close();//Fechando arquivo de saida

    //--------------------Fim Cenário 1 Main ----------------------------

    //--------------------Cenário 2 Main ----------------------------

    fstream saida2;
    saida2.open("cenario2.txt");
    saida2 << "Resultado da ordenação das variações do QuickSort" << endl << endl;

    //Leitura do arquivo rating
    for(int i = 0; i< tam_entrada; i++){
        saida2 << endl << "Resultado da ordenação para N = " << entradas[i]  << endl << endl;
        for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
            cout << endl << j << " execução para N = " << entradas[i];
            srand(2*j*i);//Sementes diferentes para cada execução de cada N

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
                    c++;//auxiliar
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
                    }else{
                        i--;
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
                estatisticaComparacoesMOV[j-1] = comparacoesMOV;
                estatisticaTrocasMOV[j-1] = trocasDeRegistroMOV;
                estatisticaTempoMOV[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
                cout<<endl<<endl<<"numero de comparacoes: " << comparacoesMOV<<endl;
                cout<<"numero de trocas de registro: " << trocasDeRegistroMOV<< endl;
                cout<<"tempo de execucao: "<< ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000 <<
                "ms"<<c<<endl << endl;
                //------------------------------------------
                delete []vetor;//Deletando vetor de movies

                arq.close();//FECHANDO O ARQUIVO DE DADOS
            }
            
        }//Fim da 5 execução de cada N
        cout << "--------------------------------------" << endl;
        //Análise dos dados para cada N
        int auxCompMov = 0;
        int auxTrocaMov = 0;
        float auxTempoMov = 0;
        for(int i = 0; i < 5; i++){
            auxCompMov+=estatisticaComparacoesMOV[i];
            auxTrocaMov+=estatisticaTrocasMOV[i];
            auxTempoMov+=estatisticaTempoMOV[i];
        }
        auxCompMov = auxCompMov/5;
        auxTrocaMov = auxTrocaMov/5;
        auxTempoMov = (float) (auxTempoMov/5);
        saida2 << endl << "Média do número de comparações: " << auxCompMov << endl;
        saida2 << "Média do número de trocas: " << auxTrocaMov << endl;
        saida2 << "Média do tempo de execução: " << auxTempoMov << "ms" << endl << endl;

    }//Fim das N execuções
    saida2.close();//Fechando arquivo de saida



    return 0;
}
