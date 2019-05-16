#include <iostream>
#include <fstream>
#include "include/movies.h"
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "hashing.h"

//ANALISAR QUAL BIBLIOTECA A GENTE PODE REMOVER, PQ SAO MUITAS

#define NINT 100 //DEFINE O TAMANHO DO VETOR DE INTEIROS A SER ORDENADO

//#define N 100 //DEFINE O TAMANHO DO VETOR DE MOVIES A SER ORDENADO
//--------------------Cenário 1 Funções ----------------------------

unsigned long int trocasDeRegistroINT = 0; //CONTADOR DAS TROCAS DE REGISTRO DO VETOR DE INTEIROS
unsigned long int comparacoesINT = 0; //CONTADOR DAS COMPARACOES DO VETOR DE INTEIROS
unsigned long int trocasDeRegistroMOV = 0; //CONTADOR DAS TROCAS DE REGISTRO DO VETOR DE MOVIES
unsigned long int comparacoesMOV = 0; //CONTADOR DAS TROCAS DE REGISTRO DO VETOR DE MOVIES

using namespace std;

//Embaralha vetor de userId 
//Porque ele já vem ordenado
void embaralha(int *vet, int tam){
    srand(time(0));
    int aleatorio = rand()%tam/2 + tam/2-1;
    int aux;
    int fim = (tam -1)/2;
    //Ate a metade do vetor troca os indices da 1 metade com os 2 metade de forma aleatoria
    for(int i = 0; i <= fim; i++){
        aux = vet[i];
        vet[i] = vet[aleatorio];
        vet[aleatorio] = aux;
        aleatorio = rand()%tam/2 + tam/2-1;
    }
}


//-------------------------------------------------------
//QUICKSORT PRA UM VETOR DE INTEIROS

void trocaDePosicao (int i, int j, int *vet)
{
    int k = vet[i];
    vet[i] = vet[j];
    vet[j] = k;
}

int particao(int start, int end, int *vet)
{   
    int pivo = vet[end];
    int i = start-1;
    for (int j = start; j < end-1; j++)
    {
        
        comparacoesINT++;
        if (vet[j] <= pivo)
        {   i++;
            trocaDePosicao(i, j, vet);
            trocasDeRegistroINT++;
        }
    }

    trocaDePosicao(i+1, end, vet);
    trocasDeRegistroINT++;
    
    return i + 1;
}

void quicksort (int start, int end, int *vet)
{   
    comparacoesINT++;
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

}

int particaoMovies(int start, int end, movies *vet)
{
    int i = start;
    for (int j = start; j < end; j++)
    {
        
        comparacoesMOV++;
        if (vet[j].movieid <= vet[end].movieid)
        {
            trocaDePosicaoMovies(i++, j, vet);
            trocasDeRegistroMOV++;
        }
    }

    trocaDePosicaoMovies(i, end, vet);
    trocasDeRegistroMOV++;

    return i;
}

void quicksortM(int start, int end, movies *vet)
{   
    comparacoesMOV++;
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
    int medianaIndice; //índice da mediana
    if(fim - inicio >= 3){
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
        comparacoesINT++;
        if (a < b) {
            comparacoesINT++;
            if (b < c) {
                //a < b && b < c
                medianaIndice = meio;
            } else {
                comparacoesINT++;
                if (a < c) {
                    //a < c && c <= b
                    medianaIndice = fim;
                } else {
                    //c <= a && a < b
                    medianaIndice = inicio;
                }
            }
        } else {
            comparacoesINT++;
            if (c < b) {
                //c < b && b <= a
                medianaIndice = meio;
            } else {
                comparacoesINT++;
                if (c < a) {
                    //b <= c && c < a
                    medianaIndice = fim;
                } else {
                    //b <= a && a <= c
                    medianaIndice = inicio;
                }
            }
        }
    }else{
        medianaIndice = fim;
    }
    //Coloca o elemento da mediana no fim para poder usar o Quicksort
    trocaPosicao2(A, medianaIndice, fim);
        
    //O pivo é o elemento final
    int pivo = A[fim];
    int i = inicio - 1;
    int j;
    //Passa os menores que o pivô para a partição da esquerda
    for (j = inicio; j <= fim - 1; j++) {
        comparacoesINT++;
        if (A[j] <= pivo) {
            i = i + 1;
            trocaPosicao2(A, i, j);
            trocasDeRegistroINT++;
        }
    }
    //Coloca o pivô na posição de ordenação
    trocaPosicao2(A, i + 1, fim);
    trocasDeRegistroINT++;
    return i + 1; //Retorna a posição do pivô
}
void quicksortMedTres(int A[], int inicio, int fim) {
    
    comparacoesINT++;
    if (inicio < fim) {
        int q = particiona2(A, inicio, fim);
        quicksortMedTres(A, inicio, q - 1);
        quicksortMedTres(A, q + 1, fim);
    }
}

//---------------QuickSort Mediana 5---------------

int particiona2Med5(int A[], int inicio, int fim) {
    int medianaIndice;//índice da mediana, que será o pivô
    comparacoesINT++;
    if(fim - inicio >= 5){
        srand(time(0));
        int indiceAleatorio[5]; // Vetor de indices aleatórios
        //Garantindo que os números aleatórios são diferentes
        for(int i = 0; i <= 4; i++){
            indiceAleatorio[i] = rand()%(fim-inicio);
            comparacoesINT++;
            while(i==1 && indiceAleatorio[i]==indiceAleatorio[i-1]){
                comparacoesINT++;
                indiceAleatorio[i] = rand()%(fim-inicio);
            }
            
            comparacoesINT++;
            while(i==2 && (indiceAleatorio[i]==indiceAleatorio[i-1] || indiceAleatorio[i]==indiceAleatorio[i-2])){
                comparacoesINT++;
                indiceAleatorio[i] = rand()%(fim-inicio);
            }

            comparacoesINT++;
            while(i==3 && (indiceAleatorio[i]==indiceAleatorio[i-1] || indiceAleatorio[i]==indiceAleatorio[i-2]
            || indiceAleatorio[i]==indiceAleatorio[i-3])){
                comparacoesINT++;
                indiceAleatorio[i] = rand()%(fim-inicio);
            }
            comparacoesINT++;
            while(i==4 && (indiceAleatorio[i]==indiceAleatorio[i-1] || indiceAleatorio[i]==indiceAleatorio[i-2]
            || indiceAleatorio[i]==indiceAleatorio[i-3] || indiceAleatorio[i]==indiceAleatorio[i-4])){
                comparacoesINT++;
                indiceAleatorio[i] = rand()%(fim-inicio);
            }
        }
        int aleatorio[5]; //Vetor com o valor dos índices aleatórios
        for(int i = 0; i <=4; i++){
            aleatorio[i] = A[indiceAleatorio[i]];
        }
        quicksort(0, 4, aleatorio);
        //procurando qual indice corresponde a mediana(aleatorio[2])
        for(int i =0; i <= 4; i++){
            comparacoesINT++;
            if(aleatorio[2] == A[indiceAleatorio[i]]){
                medianaIndice = indiceAleatorio[i];
            }
        }
    }
    else{
        medianaIndice = fim;
    }    
    //Coloca o elemento da mediana no fim para poder usar o Quicksort
    trocaPosicao2(A, medianaIndice, fim);
        
    //O pivo é o elemento final
    int pivo = A[fim];
    int i = inicio - 1;
    int j;
    //Passa os menores que o pivô para a partição da esquerda
    for (j = inicio; j <= fim - 1; j++) {
        comparacoesINT++;
        if (A[j] <= pivo) {
            i = i + 1;
            trocaPosicao2(A, i, j);
            trocasDeRegistroINT++;
        }
    }
    //Coloca o pivô na posição de ordenação
    trocaPosicao2(A, i + 1, fim);
    trocasDeRegistroINT++;
    return i + 1; //Retorna a posição do pivô
}
void quicksortMedCinco(int A[], int inicio, int fim) {
    comparacoesINT++;
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
        pivo = vet[i];
        for(j = i-1; j >= 0; j--){
            comparacoesINT++;
            trocasDeRegistroINT++;

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
{   comparacoesINT++;
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
{   comparacoesINT++;
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

void intercalaMerge(int X[], int inicio, int fim, int meio){  
    int posLivre, inicio_vetor1, inicio_vetor2;  
    int aux[fim+1]; 
    inicio_vetor1 = inicio;  
    inicio_vetor2 = meio+1;  
    posLivre = 0;  
    comparacoesINT++;
    while(inicio_vetor1 <= meio && inicio_vetor2 <= fim){  
        comparacoesINT++;
        if (X[inicio_vetor1] <= X[inicio_vetor2])  
        {   trocasDeRegistroINT++;
            aux[posLivre] = X[inicio_vetor1];  
            inicio_vetor1++;  
        }
        else{  
            trocasDeRegistroINT++;
            aux[posLivre] = X[inicio_vetor2];  
            inicio_vetor2++;  
        }  
        posLivre++;  
    }
    
    //se ainda existem numeros no primeiro vetor  
    //que nao foram intercalados  
    while (inicio_vetor1 <= meio)  
    {   trocasDeRegistroINT++;
        aux[posLivre] = X[inicio_vetor1];  
        posLivre++;  
        inicio_vetor1++;
    }  
    
    //se ainda existem numeros no segundo vetor  
    //que nao foram intercalados  
    while (inicio_vetor2 <= fim)  
    {   trocasDeRegistroINT++;
        aux[posLivre] = X[inicio_vetor2];  
        posLivre++;  
        inicio_vetor2++;
    }
    
    //retorne os valores do vetor aux para o vetor X  
    for (int i = inicio; i <=fim; i++)  
    {   trocasDeRegistroINT++;
        X[i] = aux[i];  
    }
    
}  
void merge (int X[], int inicio, int fim){ 
     
    int meio; 
    comparacoesINT++;
    if (inicio < fim)  
    {  
        meio = (inicio+fim)/2;  
        merge (X,inicio, meio);  
        merge (X,meio+1, fim);  
        intercalaMerge(X,inicio, fim, meio);  
    }  
} 

//---------------Gnome Sort (Wikipedia)--------------

void GnomeSortINT(int vet[], int tam){
    int next = 0, previous = 0;
    int i = 0;

    for(i = 0; i < tam ; i++) {
    comparacoesINT++;
        if(vet[i] > vet[i + 1]) {
            previous = i;
            next = i + 1;
            comparacoesINT++;
            while(vet[previous] > vet[next])  {
                trocaDePosicao(previous, next, vet);
                trocasDeRegistroINT++;
                
                comparacoesINT++;
                if(previous > 0)
                    previous--;
                comparacoesINT++;
                if(next > 0) 
                    next--;
            }
        }
    }
}

//--------------------Heap Sort--------------

void max_Heapify(int* vetor, int i, int tamVetor){
	int fEsq = 2*i + 1;
	int fDir = 2*i + 2;
	int max;
    comparacoesINT++;
	if(fEsq <= tamVetor && vetor[fEsq] > vetor[i] ){
		max = fEsq;
	}
	else{
		max = i;
	}
    comparacoesINT++;
	if(fDir <= tamVetor && vetor[fDir] > vetor[max]){
		max = fDir;
	}
    comparacoesINT++;
	if(max != i){
		int aux = vetor[i];
		vetor[i] = vetor[max];
		vetor[max] = aux;
        trocasDeRegistroINT++;
		max_Heapify(vetor,max,tamVetor);
	}
}

void build_Heap(int* vetor, int tamVetor){
	for(int i=tamVetor/2;i>=0;i--){
		max_Heapify(vetor,i,tamVetor);
	}
}

void Heapsort(int* vetor, int tamVetor){
	build_Heap(vetor,tamVetor);
	for(int i=tamVetor;i>=1;i--){
		int aux = vetor[0];
		vetor[0] = vetor[i];
		vetor[i] = aux;
		tamVetor--;
		max_Heapify(vetor,0,tamVetor);
	}
}



int main()
{   

    //--------------------Cenário 1 Main ----------------------------

    //PARTE DE CODIGO RELATIVA A LEITURA E ORDENACAO DE UM VETOR DE INTEIROS
    /*
    int *v = new int[NINT];
    srand(time(NULL));
    for(int i = 0; i<NINT; i++)
    {
        v[i] = rand()%200;
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
    ifstream arq;
    for(int i = 0; i< tam_entrada; i++){
        
        saida1 << endl << "Resultado da ordenação para N = " << entradas[i]  << endl << endl;
        for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
            cout << endl << j << " execução para N = " << entradas[i];
            srand(2*j*i);//Sementes diferentes para cada execução de cada N

            arq.open("ratings.csv");

            if(arq.is_open())
            {   
                int N;
                movies *vetor = new movies[entradas[i]];
                movies m;
                std::string s;
                //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, '\n');
                //--------------------------
                
                N = entradas[i];
                //LENDO O ARQUIVO----------------------
                for(int i = 0; i < N; i++)
                {   aleatorio = rand()%2;
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
                
                quicksortM(0, N, vetor);

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
                "ms"<<endl << endl;
                //------------------------------------------
                delete []vetor;//Deletando vetor de movies

                arq.close();//FECHANDO O ARQUIVO DE DADOS
            }
            
        }//Fim da 5 execução de cada N
        cout << "--------------------------------------" << endl;
        //Análise dos dados para cada N
        float auxCompMov = 0;
        float auxTrocaMov = 0;
        float auxTempoMov = 0;
        for(int i = 0; i < 5; i++){
            auxCompMov+=estatisticaComparacoesMOV[i];
            auxTrocaMov+=estatisticaTrocasMOV[i];
            auxTempoMov+=estatisticaTempoMOV[i];
        }
        auxCompMov = auxCompMov/5.0;
        auxTrocaMov = auxTrocaMov/5.0;
        auxTempoMov = (float) (auxTempoMov/5);
        saida1 << endl << "Média do número de comparações: " << auxCompMov << endl;
        saida1 << "Média do número de trocas: " << auxTrocaMov << endl;
        saida1 << "Média do tempo de execução: " << auxTempoMov << "ms" << endl << endl;

    }//Fim das N execuções
    saida1.close();//Fechando arquivo de saida

    //--------------------Fim Cenário 1 Main ----------------------------

    //--------------------Cenário 2 Main ----------------------------

    long int estatisticaComparacoesINT[5] = {0,0,0,0,0};
    long int estatisticaTrocasINT[5] = {0,0,0,0,0};
    float estatisticaTempoINT[5] = {0,0,0,0,0};

    fstream saida2;
    saida2.open("cenario2.txt");
    saida2 << "Resultado da ordenação das variações do QuickSort" << endl << endl;
    saida2 << "Resultado para o QuickSort recursivo" << endl;
    cout << "Resultado para o QuickSort recursivo" << endl;
    //Leitura do arquivo rating
    for(int i = 0; i< tam_entrada; i++){
        
        saida2 << endl << "Resultado da ordenação para N = " << entradas[i]  << endl << endl;
        for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
            cout << endl << j << " execução para N = " << entradas[i];
            srand(2*j*(i+1));//Sementes diferentes para cada execução de cada N

            arq.open("ratings.csv");

            if(arq.is_open())
            {   
                int N = entradas[i];
                int *vetor = new int[N];
                int m;
                std::string s;
                //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, '\n');
                //--------------------------
                
                //LENDO O ARQUIVO----------------------
                for(int i = 0; i < N; i++)
                {   aleatorio = rand()%2;
                    if(aleatorio==1){
                        getline(arq, s, ',');
                        m = atoi(s.c_str());

                        getline(arq, s, ',');

                        getline(arq, s, ',');
                        
                        getline(arq, s, '\n');
                        
                        vetor[i] = m;
                    }else{
                        i--;
                    }
                }
                embaralha(vetor, N);
                //APLICANDO O QUICKSORT
                clock_t fim, inicio;
                trocasDeRegistroINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                comparacoesINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                inicio = clock();
                quicksort(0, N-1, vetor);
                fim = clock();
                //--------------------

                
                estatisticaComparacoesINT[j-1] = comparacoesINT;
                estatisticaTrocasINT[j-1] = trocasDeRegistroINT;
                estatisticaTempoINT[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
                cout<<endl<<endl<<"numero de comparacoes: " << comparacoesINT<<endl;
                cout<<"numero de trocas de registro: " << trocasDeRegistroINT<< endl;
                cout<<"tempo de execucao: "<< ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000 <<
                "ms"<<endl << endl;
                //------------------------------------------
                delete []vetor;//Deletando vetor de movies

                arq.close();//FECHANDO O ARQUIVO DE DADOS
            }
            
        }//Fim da 5 execução de cada N
        cout << "--------------------------------------" << endl;
        //Análise dos dados para cada N
        float auxCompINT = 0;
        float auxTrocaINT = 0;
        float auxTempoINT = 0;
        for(int i = 0; i < 5; i++){
            auxCompINT += estatisticaComparacoesINT[i];
            auxTrocaINT += estatisticaTrocasINT[i];
            auxTempoINT += estatisticaTempoINT[i];
        }
        auxCompINT = auxCompINT/5;
        auxTrocaINT = auxTrocaINT/5;
        auxTempoINT = (float) (auxTempoINT/5);
        saida2 << endl << "Média do número de comparações: " << auxCompINT << endl;
        saida2 << "Média do número de trocas: " << auxTrocaINT << endl;
        saida2 << "Média do tempo de execução: " << auxTempoINT << "ms" << endl << endl;

    }
    

    saida2 << "Resultado para o QuickSort Mediana K = 3" << endl;
    cout << "Resultado para o QuickSort Mediana K = 3" << endl;
    //Leitura do arquivo rating
    
    for(int i = 0; i< tam_entrada; i++){
        int N = entradas[i];
        saida2 << endl << "Resultado da ordenação para N = " << N << endl << endl;
        for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
            cout << endl << j << " execução para N = " << N;
            srand(2*j*(i+1));//Sementes diferentes para cada execução de cada N

            arq.open("ratings.csv");

            if(arq.is_open())
            {   
                int *vetor = new int[N];
                int m;
                std::string s;
                //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, '\n');
                //--------------------------
                
                //LENDO O ARQUIVO----------------------
                for(int i = 0; i < N; i++)
                {   aleatorio = rand()%2;
                    if(aleatorio==1){
                        getline(arq, s, ',');
                        m = atoi(s.c_str());

                        getline(arq, s, ',');

                        getline(arq, s, ',');
                        
                        getline(arq, s, '\n');
                        
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
                embaralha(vetor, N);
                //APLICANDO O QUICKSORT
                clock_t fim, inicio;
                inicio = clock();
                trocasDeRegistroINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                comparacoesINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                
                quicksortMedTres(vetor, 0, N-1);

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
                estatisticaComparacoesINT[j-1] = comparacoesINT;
                estatisticaTrocasINT[j-1] = trocasDeRegistroINT;
                estatisticaTempoINT[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
                cout<<endl<<endl<<"numero de comparacoes: " << comparacoesINT<<endl;
                cout<<"numero de trocas de registro: " << trocasDeRegistroINT<< endl;
                cout<<"tempo de execucao: "<< ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000 <<
                "ms"<<endl << endl;
                //------------------------------------------
                delete []vetor;//Deletando vetor de movies

                arq.close();//FECHANDO O ARQUIVO DE DADOS
            }else{
                cout << "erro arquivo!" << endl;
            }
            
        }//Fim da 5 execução de cada N
        cout << "--------------------------------------" << endl;
        //Análise dos dados para cada N
        float auxCompINT = 0;
        float auxTrocaINT = 0;
        float auxTempoINT = 0;
        for(int i = 0; i < 5; i++){
            auxCompINT+=estatisticaComparacoesINT[i];
            auxTrocaINT+=estatisticaTrocasINT[i];
            auxTempoINT+=estatisticaTempoINT[i];
        }
        auxCompINT = auxCompINT/5;
        auxTrocaINT = auxTrocaINT/5;
        auxTempoINT = (float) (auxTempoINT/5);
        saida2 << endl << "Média do número de comparações: " << auxCompINT << endl;
        saida2 << "Média do número de trocas: " << auxTrocaINT << endl;
        saida2 << "Média do tempo de execução: " << auxTempoINT << "ms" << endl << endl;

    }
    
    saida2 << "Resultado para o QuickSort Mediana K = 5" << endl;
    cout << "Resultado para o QuickSort Mediana K = 5" << endl;
    //Leitura do arquivo rating
    
    for(int i = 0; i< tam_entrada; i++){
        
        saida2 << endl << "Resultado da ordenação para N = " << entradas[i]  << endl << endl;
        for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
            cout << endl << j << " execução para N = " << entradas[i];
            srand(2*j*(i+1));//Sementes diferentes para cada execução de cada N

            arq.open("ratings.csv");

            if(arq.is_open())
            {   
                int N = entradas[i];
                int *vetor = new int[N];
                int m;
                std::string s;
                //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, '\n');
                //--------------------------
                
                //LENDO O ARQUIVO----------------------
                for(int i = 0; i < N; i++)
                {   aleatorio = rand()%2;
                    if(aleatorio==1){
                        getline(arq, s, ',');
                        m = atoi(s.c_str());

                        getline(arq, s, ',');

                        getline(arq, s, ',');
                        
                        getline(arq, s, '\n');
                        
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
                embaralha(vetor, N);
                //APLICANDO O QUICKSORT
                clock_t fim, inicio;
                inicio = clock();
                trocasDeRegistroINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                comparacoesINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                
                quicksortMedCinco(vetor, 0, N-1);

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
                estatisticaComparacoesINT[j-1] = comparacoesINT;
                estatisticaTrocasINT[j-1] = trocasDeRegistroINT;
                estatisticaTempoINT[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
                cout<<endl<<endl<<"numero de comparacoes: " << comparacoesINT<<endl;
                cout<<"numero de trocas de registro: " << trocasDeRegistroINT<< endl;
                cout<<"tempo de execucao: "<< ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000 <<
                "ms"<<endl << endl;
                //------------------------------------------
                delete []vetor;//Deletando vetor de movies

                arq.close();//FECHANDO O ARQUIVO DE DADOS
            }
            
        }//Fim da 5 execução de cada N
        cout << "--------------------------------------" << endl;
        //Análise dos dados para cada N
        float auxCompINT = 0;
        float auxTrocaINT = 0;
        float auxTempoINT = 0;
        for(int i = 0; i < 5; i++){
            auxCompINT+=estatisticaComparacoesINT[i];
            auxTrocaINT+=estatisticaTrocasINT[i];
            auxTempoINT+=estatisticaTempoINT[i];
        }
        auxCompINT = auxCompINT/5;
        auxTrocaINT = auxTrocaINT/5;
        auxTempoINT = (float) (auxTempoINT/5);
        saida2 << endl << "Média do número de comparações: " << auxCompINT << endl;
        saida2 << "Média do número de trocas: " << auxTrocaINT << endl;
        saida2 << "Média do tempo de execução: " << auxTempoINT << "ms" << endl << endl;

    }
    
    saida2 << "Resultado para o QuickInsertionSort M = 10 " << endl;
    cout << "Resultado para o QuickInsertionSort M = 10 " << endl;
    //Leitura do arquivo rating
    
    for(int i = 0; i< tam_entrada; i++){
        
        saida2 << endl << "Resultado da ordenação para N = " << entradas[i]  << endl << endl;
        for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
            cout << endl << j << " execução para N = " << entradas[i];
            srand(2*j*(i+1));//Sementes diferentes para cada execução de cada N

            arq.open("ratings.csv");

            if(arq.is_open())
            {   
                int N = entradas[i];
                int *vetor = new int[N];
                int m;
                std::string s;
                //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, '\n');
                //--------------------------
                
                //LENDO O ARQUIVO----------------------
                for(int i = 0; i < N; i++)
                {   aleatorio = rand()%2;
                    if(aleatorio==1){
                        getline(arq, s, ',');
                        m = atoi(s.c_str());

                        getline(arq, s, ',');

                        getline(arq, s, ',');
                        
                        getline(arq, s, '\n');
                        
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
                embaralha(vetor, N);
                //APLICANDO O QUICKSORT
                clock_t fim, inicio;
                inicio = clock();
                trocasDeRegistroINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                comparacoesINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                
                QuickInsertionSort10(0, N, vetor);

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
                estatisticaComparacoesINT[j-1] = comparacoesINT;
                estatisticaTrocasINT[j-1] = trocasDeRegistroINT;
                estatisticaTempoINT[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
                cout<<endl<<endl<<"numero de comparacoes: " << comparacoesINT<<endl;
                cout<<"numero de trocas de registro: " << trocasDeRegistroINT<< endl;
                cout<<"tempo de execucao: "<< ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000 <<
                "ms"<<endl << endl;
                //------------------------------------------
                delete []vetor;//Deletando vetor de movies

                arq.close();//FECHANDO O ARQUIVO DE DADOS
            }
            
        }//Fim da 5 execução de cada N
        cout << "--------------------------------------" << endl;
        //Análise dos dados para cada N
        float auxCompINT = 0;
        float auxTrocaINT = 0;
        float auxTempoINT = 0;
        for(int i = 0; i < 5; i++){
            auxCompINT+=estatisticaComparacoesINT[i];
            auxTrocaINT+=estatisticaTrocasINT[i];
            auxTempoINT+=estatisticaTempoINT[i];
        }
        auxCompINT = auxCompINT/5;
        auxTrocaINT = auxTrocaINT/5;
        auxTempoINT = (float) (auxTempoINT/5);
        saida2 << endl << "Média do número de comparações: " << auxCompINT << endl;
        saida2 << "Média do número de trocas: " << auxTrocaINT << endl;
        saida2 << "Média do tempo de execução: " << auxTempoINT << "ms" << endl << endl;

    }
    
    saida2 << "Resultado para o QuickInsertionSort100" << endl;
    cout << "Resultado para o QuickInsertionSort M = 100 " << endl;
    //Leitura do arquivo rating
    
    for(int i = 0; i< tam_entrada; i++){
        
        saida2 << endl << "Resultado da ordenação para N = " << entradas[i]  << endl << endl;
        for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
            cout << endl << j << " execução para N = " << entradas[i];
            srand(2*j*(i+1));//Sementes diferentes para cada execução de cada N

            arq.open("ratings.csv");

            if(arq.is_open())
            {   
                int N = entradas[i];
                int *vetor = new int[N];
                int m;
                std::string s;
                //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, '\n');
                //--------------------------
                
                //LENDO O ARQUIVO----------------------
                for(int i = 0; i < N; i++)
                {   aleatorio = rand()%2;
                    if(aleatorio==1){
                        getline(arq, s, ',');
                        m = atoi(s.c_str());

                        getline(arq, s, ',');

                        getline(arq, s, ',');
                        
                        getline(arq, s, '\n');
                        
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
                embaralha(vetor, N);
                //APLICANDO O QUICKSORT
                clock_t fim, inicio;
                inicio = clock();
                trocasDeRegistroINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                comparacoesINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                
                QuickInsertionSort100(0, N, vetor);

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
                estatisticaComparacoesINT[j-1] = comparacoesINT;
                estatisticaTrocasINT[j-1] = trocasDeRegistroINT;
                estatisticaTempoINT[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
                cout<<endl<<endl<<"numero de comparacoes: " << comparacoesINT<<endl;
                cout<<"numero de trocas de registro: " << trocasDeRegistroINT<< endl;
                cout<<"tempo de execucao: "<< ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000 <<
                "ms"<<endl << endl;
                //------------------------------------------
                delete []vetor;//Deletando vetor de movies

                arq.close();//FECHANDO O ARQUIVO DE DADOS
            }
            
        }//Fim da 5 execução de cada N
        cout << "--------------------------------------" << endl;
        //Análise dos dados para cada N
        float auxCompINT = 0;
        float auxTrocaINT = 0;
        float auxTempoINT = 0;
        for(int i = 0; i < 5; i++){
            auxCompINT+=estatisticaComparacoesINT[i];
            auxTrocaINT+=estatisticaTrocasINT[i];
            auxTempoINT+=estatisticaTempoINT[i];
        }
        auxCompINT = auxCompINT/5.0;
        auxTrocaINT = auxTrocaINT/5.0;
        auxTempoINT = (float) (auxTempoINT/5);
        saida2 << endl << "Média do número de comparações: " << auxCompINT << endl;
        saida2 << "Média do número de trocas: " << auxTrocaINT << endl;
        saida2 << "Média do tempo de execução: " << auxTempoINT << "ms" << endl << endl;

    }
    

    saida2.close();//Fechando arquivo de saida
//*******************FIM DO CENÁRIO 2 *****************

//*********************CENÁRIO 3 MAIN*******************

    fstream saida3;
    saida3.open("cenario3.txt");
    //trocar pelo sort escolhido
    saida3 << "Resultado para o QuickSort " << endl;
    cout << "Cenario 3:" << endl << endl;
    cout << "Resultado para o QuickSort Insertion " << endl;
    //Leitura do arquivo rating
    
    for(int i = 0; i< tam_entrada; i++){
        
        saida3 << endl << "Resultado da ordenação para N = " << entradas[i]  << endl << endl;
        for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
            cout << endl << j << " execução para N = " << entradas[i];
            srand(2*j*(i+1));//Sementes diferentes para cada execução de cada N

            arq.open("ratings.csv");

            if(arq.is_open())
            {   
                int N = entradas[i];
                int *vetor = new int[N];
                int m;
                std::string s;
                //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, '\n');
                //--------------------------
                
                //LENDO O ARQUIVO----------------------
                for(int i = 0; i < N; i++)
                {   aleatorio = rand()%2;
                    if(aleatorio==1){
                        getline(arq, s, ',');
                        m = atoi(s.c_str());

                        getline(arq, s, ',');

                        getline(arq, s, ',');
                        
                        getline(arq, s, '\n');
                        
                        vetor[i] = m;
                    }else{
                        i--;
                    }
                }
                embaralha(vetor, N);
                //APLICANDO O QUICKSORT
                clock_t fim, inicio;
                inicio = clock();
                trocasDeRegistroINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                comparacoesINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                
                QuickInsertionSort10(0, N, vetor);
                fim = clock();
                //--------------------

                
                estatisticaComparacoesINT[j-1] = comparacoesINT;
                estatisticaTrocasINT[j-1] = trocasDeRegistroINT;
                estatisticaTempoINT[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
                cout<<endl<<endl<<"numero de comparacoes: " << comparacoesINT<<endl;
                cout<<"numero de trocas de registro: " << trocasDeRegistroINT<< endl;
                cout<<"tempo de execucao: "<< ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000 <<
                "ms"<<endl << endl;
                //------------------------------------------
                delete []vetor;//Deletando vetor de movies

                arq.close();//FECHANDO O ARQUIVO DE DADOS
            }
            
        }//Fim da 5 execução de cada N
        cout << "--------------------------------------" << endl;
        //Análise dos dados para cada N
        float auxCompINT = 0;
        float auxTrocaINT = 0;
        float auxTempoINT = 0;
        for(int i = 0; i < 5; i++){
            auxCompINT += estatisticaComparacoesINT[i];
            auxTrocaINT += estatisticaTrocasINT[i];
            auxTempoINT += estatisticaTempoINT[i];
        }
        auxCompINT = auxCompINT/5;
        auxTrocaINT = auxTrocaINT/5;
        auxTempoINT = (float) (auxTempoINT/5);
        saida3 << endl << "Média do número de comparações: " << auxCompINT << endl;
        saida3 << "Média do número de trocas: " << auxTrocaINT << endl;
        saida3 << "Média do tempo de execução: " << auxTempoINT << "ms" << endl << endl;

    }
    
    saida3 << "Resultado para o MergeSort" << endl;
    cout << "Resultado para o MergeSort" << endl;
    //Leitura do arquivo rating
    
    for(int i = 0; i< tam_entrada; i++){
        
        saida3 << endl << "Resultado da ordenação para N = " << entradas[i]  << endl << endl;
        for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
            cout << endl << j << " execução para N = " << entradas[i] << endl;
            srand(2*j*(i+1));//Sementes diferentes para cada execução de cada N

            arq.open("ratings.csv");

            if(arq.is_open())
            {   
                int N = entradas[i];
                int *vetor = new int[N];
                int m;
                std::string s;
                //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, '\n');
                //--------------------------
                
                //LENDO O ARQUIVO----------------------
                for(int i = 0; i < N; i++)
                {   aleatorio = rand()%2;
                    if(aleatorio==1){
                        getline(arq, s, ',');
                        m = atoi(s.c_str());

                        getline(arq, s, ',');

                        getline(arq, s, ',');
                        
                        getline(arq, s, '\n');
                        
                        vetor[i] = m;
                    }else{
                        i--;
                    }
                }
                embaralha(vetor, N);
                //APLICANDO O QUICKSORT
                clock_t fim, inicio;
                inicio = clock();
                trocasDeRegistroINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                comparacoesINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                
                merge(vetor, 0, N-1);

                fim = clock();
                //--------------------

                
                estatisticaComparacoesINT[j-1] = comparacoesINT;
                estatisticaTrocasINT[j-1] = trocasDeRegistroINT;
                estatisticaTempoINT[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
                cout<<endl<<endl<<"numero de comparacoes: " << comparacoesINT<<endl;
                cout<<"numero de trocas de registro: " << trocasDeRegistroINT<< endl;
                cout<<"tempo de execucao: "<< ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000 <<
                "ms"<<endl << endl;
                //------------------------------------------
                delete []vetor;//Deletando vetor de movies

                arq.close();//FECHANDO O ARQUIVO DE DADOS
            }
            
        }//Fim da 5 execução de cada N
        cout << "--------------------------------------" << endl;
        //Análise dos dados para cada N
        float auxCompINT = 0;
        float auxTrocaINT = 0;
        float auxTempoINT = 0;
        for(int i = 0; i < 5; i++){
            auxCompINT += estatisticaComparacoesINT[i];
            auxTrocaINT += estatisticaTrocasINT[i];
            auxTempoINT += estatisticaTempoINT[i];
        }
        auxCompINT = auxCompINT/5;
        auxTrocaINT = auxTrocaINT/5;
        auxTempoINT = (float) (auxTempoINT/5);
        saida3 << endl << "Média do número de comparações: " << auxCompINT << endl;
        saida3 << "Média do número de trocas: " << auxTrocaINT << endl;
        saida3 << "Média do tempo de execução: " << auxTempoINT << "ms" << endl << endl;

    }

    saida3 << "Resultado para o HeapSort" << endl;
    cout << "Resultado para o HeapSort" << endl;
    //Leitura do arquivo rating
    
    for(int i = 0; i< tam_entrada; i++){
        
        saida3 << endl << "Resultado da ordenação para N = " << entradas[i]  << endl << endl;
        for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
            cout << endl << j << " execução para N = " << entradas[i];
            srand(2*j*(i+1));//Sementes diferentes para cada execução de cada N

            arq.open("ratings.csv");

            if(arq.is_open())
            {   
                int N = entradas[i];
                int *vetor = new int[N];
                int m;
                std::string s;
                //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, '\n');
                //--------------------------
                
                //LENDO O ARQUIVO----------------------
                for(int i = 0; i < N; i++)
                {   aleatorio = rand()%2;
                    if(aleatorio==1){
                        getline(arq, s, ',');
                        m = atoi(s.c_str());

                        getline(arq, s, ',');

                        getline(arq, s, ',');
                        
                        getline(arq, s, '\n');
                        
                        vetor[i] = m;
                    }else{
                        i--;
                    }
                }
                embaralha(vetor, N);
                //APLICANDO O QUICKSORT
                clock_t fim, inicio;
                inicio = clock();
                trocasDeRegistroINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                comparacoesINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                
                Heapsort(vetor, N-1);

                fim = clock();
                //--------------------

                
                estatisticaComparacoesINT[j-1] = comparacoesINT;
                estatisticaTrocasINT[j-1] = trocasDeRegistroINT;
                estatisticaTempoINT[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
                cout<<endl<<endl<<"numero de comparacoes: " << comparacoesINT<<endl;
                cout<<"numero de trocas de registro: " << trocasDeRegistroINT<< endl;
                cout<<"tempo de execucao: "<< ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000 <<
                "ms"<<endl << endl;
                //------------------------------------------
                delete []vetor;//Deletando vetor de movies

                arq.close();//FECHANDO O ARQUIVO DE DADOS
            }
            
        }//Fim da 5 execução de cada N
        cout << "--------------------------------------" << endl;
        //Análise dos dados para cada N
        float auxCompINT = 0;
        float auxTrocaINT = 0;
        float auxTempoINT = 0;
        for(int i = 0; i < 5; i++){
            auxCompINT += estatisticaComparacoesINT[i];
            auxTrocaINT += estatisticaTrocasINT[i];
            auxTempoINT += estatisticaTempoINT[i];
        }
        auxCompINT = auxCompINT/5;
        auxTrocaINT = auxTrocaINT/5;
        auxTempoINT = (float) (auxTempoINT/5);
        saida3 << endl << "Média do número de comparações: " << auxCompINT << endl;
        saida3 << "Média do número de trocas: " << auxTrocaINT << endl;
        saida3 << "Média do tempo de execução: " << auxTempoINT << "ms" << endl << endl;

    }

    saida3 << "Resultado para o Insertion" << endl;
    cout << "Resultado para o Insertion" << endl;
    //Leitura do arquivo rating
    
    for(int i = 0; i< tam_entrada; i++){
        
        saida3 << endl << "Resultado da ordenação para N = " << entradas[i]  << endl << endl;
        for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
            cout << endl << j << " execução para N = " << entradas[i];
            srand(2*j*(i+1));//Sementes diferentes para cada execução de cada N

            arq.open("ratings.csv");

            if(arq.is_open())
            {   
                int N = entradas[i];
                int *vetor = new int[N];
                int m;
                std::string s;
                //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, '\n');
                //--------------------------
                
                //LENDO O ARQUIVO----------------------
                for(int i = 0; i < N; i++)
                {   aleatorio = rand()%2;
                    if(aleatorio==1){
                        getline(arq, s, ',');
                        m = atoi(s.c_str());

                        getline(arq, s, ',');

                        getline(arq, s, ',');
                        
                        getline(arq, s, '\n');
                        
                        vetor[i] = m;
                    }else{
                        i--;
                    }
                }
                embaralha(vetor, N);
                //APLICANDO O QUICKSORT
                clock_t fim, inicio;
                inicio = clock();
                trocasDeRegistroINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                comparacoesINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                
                InsertionSort(vetor, N);

                fim = clock();
                //--------------------

                
                estatisticaComparacoesINT[j-1] = comparacoesINT;
                estatisticaTrocasINT[j-1] = trocasDeRegistroINT;
                estatisticaTempoINT[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
                cout<<endl<<endl<<"numero de comparacoes: " << comparacoesINT<<endl;
                cout<<"numero de trocas de registro: " << trocasDeRegistroINT<< endl;
                cout<<"tempo de execucao: "<< ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000 <<
                "ms"<<endl << endl;
                //------------------------------------------
                delete []vetor;//Deletando vetor de movies

                arq.close();//FECHANDO O ARQUIVO DE DADOS
            }
            
        }//Fim da 5 execução de cada N
        cout << "--------------------------------------" << endl;
        //Análise dos dados para cada N
        float auxCompINT = 0;
        float auxTrocaINT = 0;
        float auxTempoINT = 0;
        for(int i = 0; i < 5; i++){
            auxCompINT += estatisticaComparacoesINT[i];
            auxTrocaINT += estatisticaTrocasINT[i];
            auxTempoINT += estatisticaTempoINT[i];
        }
        auxCompINT = auxCompINT/5;
        auxTrocaINT = auxTrocaINT/5;
        auxTempoINT = (float) (auxTempoINT/5);
        saida3 << endl << "Média do número de comparações: " << auxCompINT << endl;
        saida3 << "Média do número de trocas: " << auxTrocaINT << endl;
        saida3 << "Média do tempo de execução: " << auxTempoINT << "ms" << endl << endl;

    }

    saida3 << "Resultado para o GnomeSort" << endl;
    cout << "Resultado para o GnomeSort" << endl;
    //Leitura do arquivo rating
    
    for(int i = 0; i< tam_entrada; i++){
        
        saida3 << endl << "Resultado da ordenação para N = " << entradas[i]  << endl << endl;
        for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
            cout << endl << j << " execução para N = " << entradas[i];
            srand(2*j*(i+1));//Sementes diferentes para cada execução de cada N

            arq.open("ratings.csv");

            if(arq.is_open())
            {   
                int N = entradas[i];
                int *vetor = new int[N];
                int m;
                std::string s;
                //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, ',');
                getline(arq, s, '\n');
                //--------------------------
                
                //LENDO O ARQUIVO----------------------
                for(int i = 0; i < N; i++)
                {   aleatorio = rand()%2;
                    if(aleatorio==1){
                        getline(arq, s, ',');
                        m = atoi(s.c_str());

                        getline(arq, s, ',');

                        getline(arq, s, ',');
                        
                        getline(arq, s, '\n');
                        
                        vetor[i] = m;
                    }else{
                        i--;
                    }
                }
                embaralha(vetor, N);
                //APLICANDO O QUICKSORT
                clock_t fim, inicio;
                inicio = clock();
                trocasDeRegistroINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                comparacoesINT = 0;//GARANTINDO QUE AS VARIAVEIS GLOBAIS SAO NULAS ANTES DO QUICKSORT
                
                GnomeSortINT(vetor, N);

                fim = clock();
                //--------------------

                
                estatisticaComparacoesINT[j-1] = comparacoesINT;
                estatisticaTrocasINT[j-1] = trocasDeRegistroINT;
                estatisticaTempoINT[j-1] = ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000;
                cout<<endl<<endl<<"numero de comparacoes: " << comparacoesINT<<endl;
                cout<<"numero de trocas de registro: " << trocasDeRegistroINT<< endl;
                cout<<"tempo de execucao: "<< ((float)(fim - inicio)/CLOCKS_PER_SEC)*1000 <<
                "ms"<<endl << endl;
                //------------------------------------------
                delete []vetor;//Deletando vetor de movies

                arq.close();//FECHANDO O ARQUIVO DE DADOS
            }
            
        }//Fim da 5 execução de cada N
        cout << "--------------------------------------" << endl;
        //Análise dos dados para cada N
        float auxCompINT = 0;
        float auxTrocaINT = 0;
        float auxTempoINT = 0;
        for(int i = 0; i < 5; i++){
            auxCompINT += estatisticaComparacoesINT[i];
            auxTrocaINT += estatisticaTrocasINT[i];
            auxTempoINT += estatisticaTempoINT[i];
        }
        auxCompINT = auxCompINT/5;
        auxTrocaINT = auxTrocaINT/5;
        auxTempoINT = (float) (auxTempoINT/5);
        saida3 << endl << "Média do número de comparações: " << auxCompINT << endl;
        saida3 << "Média do número de trocas: " << auxTrocaINT << endl;
        saida3 << "Média do tempo de execução: " << auxTempoINT << "ms" << endl << endl;

    }
    saida3.close();//Fechando arquivo de saida

//**************MAIN CENÁRIO 4******************

cout << "Cenário 4" << endl;

long int vetEspaco[5] = {0, 0, 0, 0, 0}; // espaco utilizado para cada N
long int vetColisoes[5] = {0, 0, 0, 0, 0}; // numero de colisoes para cada N

fstream saida4;
saida4.open("cenario4.txt");
for(int i = 0; i< tam_entrada; i++){
        
    saida4 << endl << "Resultado do Encadeamento Coalescido para N = " 
    << entradas[i] << endl << endl;
    cout << endl << "Resultado do Encadeamento Coalescido para N = " 
    << entradas[i] << endl << endl;
    for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
        cout << endl << j << " execução para N = " << entradas[i] << endl;
        srand(2*j*(i+1));//Sementes diferentes para cada execução de cada N

        arq.open("ratings.csv");

        if(arq.is_open())
        {   
            int N = entradas[i];
            ECoalescido* tabela = new ECoalescido(N);
            DuplaMovies auxDupla = DuplaMovies(); //armazena a dupla temporariamente
            //para colocar na tabela
            int AuxUserId;//armazena userid temporariamente para leitura
            int AuxMovieId;//armazena movieid temporariamente para leitura
            std::string s;
            //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
            getline(arq, s, ',');
            getline(arq, s, ',');
            getline(arq, s, ',');
            getline(arq, s, '\n');
            //--------------------------
            
            //LENDO O ARQUIVO E ADICIONANDO NO HASH
            for(int i = 0; i < N; i++)
            {   aleatorio = rand()%2;
                if(aleatorio==1){
                    getline(arq, s, ',');
                    AuxUserId = atoi(s.c_str());

                    getline(arq, s, ',');
                    AuxMovieId = atoi(s.c_str());

                    getline(arq, s, ',');
                    
                    getline(arq, s, '\n');
                    
                    auxDupla.setUser(AuxUserId);
                    auxDupla.setMovies(AuxMovieId);
                    tabela->inserir(auxDupla);//como saber se foi inserido ou nao?
                }else{//se nao tiver nenhum retorno vai inserir -1 elementos
                    i--;//coloca retorno no inserir boolean?
                }
            }
            cout << "colisoes " << tabela->qtdColisoes()<< endl;
            cout << "memoria: " << 3*N << endl; // Gasto constante (a tabela eh fixa)
    
            vetEspaco[j-1] = 3*N;
            vetColisoes[j-1] = tabela->qtdColisoes();
            //------------------------------------------
            delete tabela;//Deletando vetor de movies
            
            arq.close();//FECHANDO O ARQUIVO DE DADOS
        }
        
    }//Fim da 5 execução de cada N
    cout << "--------------------------------------" << endl;
    //Análise dos dados para cada N

    float auxMediaEspaco = 0;
    float auxMediaColisao = 0;
    for(int i=0; i< 5; i++){
        auxMediaEspaco += vetEspaco[i];
        auxMediaColisao += vetColisoes[i];
    }
    auxMediaColisao = auxMediaColisao/5;
    auxMediaEspaco = auxMediaEspaco/5;

    saida4 << "Media de colisoes: " << auxMediaColisao << endl;
    saida4 << "Meida de memoria gasta: " << auxMediaEspaco << endl;
}
    
    
for(int i = 0; i< tam_entrada; i++){
        
    saida4 << endl << "Resultado do Encadeamento Separado para N = " 
    << entradas[i] << endl << endl;
    cout << endl << "Resultado do Encadeamento Separado para N = " 
    << entradas[i] << endl << endl;
    for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
        cout << endl << j << " execução para N = " << entradas[i] << endl;
        srand(2*j*(i+1));//Sementes diferentes para cada execução de cada N

        arq.open("ratings.csv");

        if(arq.is_open())
        {   
            int N = entradas[i];
            ESeparado* tabela = new ESeparado(N);
            DuplaMovies auxDupla = DuplaMovies(); //armazena a dupla temporariamente
            //para colocar na tabela
            int AuxUserId;//armazena userid temporariamente para leitura
            int AuxMovieId;//armazena movieid temporariamente para leitura
            std::string s;
            //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
            getline(arq, s, ',');
            getline(arq, s, ',');
            getline(arq, s, ',');
            getline(arq, s, '\n');
            //--------------------------
            
            //LENDO O ARQUIVO E ADICIONANDO NO HASH
            for(int i = 0; i < N; i++)
            {   aleatorio = rand()%2;
                if(aleatorio==1){
                    getline(arq, s, ',');
                    AuxUserId = atoi(s.c_str());

                    getline(arq, s, ',');
                    AuxMovieId = atoi(s.c_str());

                    getline(arq, s, ',');
                    
                    getline(arq, s, '\n');
                    
                    auxDupla.setUser(AuxUserId);
                    auxDupla.setMovies(AuxMovieId);
                    tabela->inserir(auxDupla);//como saber se foi inserido ou nao?
                }else{//se nao tiver nenhum retorno vai inserir -1 elementos
                    i--;//coloca retorno no inserir boolean?
                }
            }
            cout << "colisoes " << tabela->qtdColisoes()<< endl;
            cout << "memoria: " << tabela->getMemoriaGasta() << endl;
    
            vetEspaco[j-1] = tabela->getMemoriaGasta();
            vetColisoes[j-1] = tabela->qtdColisoes();
            //------------------------------------------
            delete tabela;//Deletando vetor de movies
            
            arq.close();//FECHANDO O ARQUIVO DE DADOS
        }
        
    }//Fim da 5 execução de cada N
    cout << "--------------------------------------" << endl;
    //Análise dos dados para cada N

    float auxMediaEspaco = 0;
    float auxMediaColisao = 0;
    for(int i=0; i< 5; i++){
        auxMediaEspaco += vetEspaco[i];
        auxMediaColisao += vetColisoes[i];
    }
    auxMediaColisao = auxMediaColisao/5;
    auxMediaEspaco = auxMediaEspaco/5;

    saida4 << "Media de colisoes: " << auxMediaColisao << endl;
    saida4 << "Meida de memoria gasta: " << auxMediaEspaco << endl;
}
    
    
for(int i = 0; i< tam_entrada; i++){
        
    saida4 << endl << "Resultado do Sondagem linear para N = " 
    << entradas[i] << endl << endl;
    cout << endl << "Resultado do Sondagem Linear para N = " 
    << entradas[i] << endl << endl;
    for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
        cout << endl << j << " execução para N = " << entradas[i] << endl;
        srand(2*j*(i+1));//Sementes diferentes para cada execução de cada N

        arq.open("ratings.csv");

        if(arq.is_open())
        {   
            int N = entradas[i];
            SLinear* tabela = new SLinear(N);
            DuplaMovies auxDupla = DuplaMovies(); //armazena a dupla temporariamente
            //para colocar na tabela
            int AuxUserId;//armazena userid temporariamente para leitura
            int AuxMovieId;//armazena movieid temporariamente para leitura
            std::string s;
            //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
            getline(arq, s, ',');
            getline(arq, s, ',');
            getline(arq, s, ',');
            getline(arq, s, '\n');
            //--------------------------
            
            //LENDO O ARQUIVO E ADICIONANDO NO HASH
            for(int i = 0; i < N; i++)
            {   aleatorio = rand()%2;
                if(aleatorio==1){
                    getline(arq, s, ',');
                    AuxUserId = atoi(s.c_str());

                    getline(arq, s, ',');
                    AuxMovieId = atoi(s.c_str());

                    getline(arq, s, ',');
                    
                    getline(arq, s, '\n');
                    
                    auxDupla.setUser(AuxUserId);
                    auxDupla.setMovies(AuxMovieId);
                    tabela->inserir(auxDupla);//como saber se foi inserido ou nao?
                }else{//se nao tiver nenhum retorno vai inserir -1 elementos
                    i--;//coloca retorno no inserir boolean?
                }
            }
            cout << "colisoes " << tabela->qtdColisoes()<< endl;
            cout << "memoria: " << tabela->getPosOcupadas() << endl;
    
            vetEspaco[j-1] = tabela->getPosOcupadas();
            vetColisoes[j-1] = tabela->qtdColisoes();
            //------------------------------------------
            delete tabela;//Deletando vetor de movies
            
            arq.close();//FECHANDO O ARQUIVO DE DADOS
        }
        
    }//Fim da 5 execução de cada N
    cout << "--------------------------------------" << endl;
    //Análise dos dados para cada N

    float auxMediaEspaco = 0;
    float auxMediaColisao = 0;
    for(int i=0; i< 5; i++){
        auxMediaEspaco += vetEspaco[i];
        auxMediaColisao += vetColisoes[i];
    }
    auxMediaColisao = auxMediaColisao/5;
    auxMediaEspaco = auxMediaEspaco/5;

    saida4 << "Media de colisoes: " << auxMediaColisao << endl;
    saida4 << "Meida de memoria gasta: " << auxMediaEspaco << endl;
}
    
for(int i = 0; i< tam_entrada; i++){
        
    saida4 << endl << "Resultado do Sondagem quadrática para N = " 
    << entradas[i] << endl << endl;
    cout << endl << "Resultado do Sondagem quadrática para N = " 
    << entradas[i] << endl << endl;
    for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
        cout << endl << j << " execução para N = " << entradas[i] << endl;
        srand(2*j*(i+1));//Sementes diferentes para cada execução de cada N

        arq.open("ratings.csv");

        if(arq.is_open())
        {   
            int N = entradas[i];
            SQuadratica* tabela = new SQuadratica(N);
            DuplaMovies auxDupla = DuplaMovies(); //armazena a dupla temporariamente
            //para colocar na tabela
            int AuxUserId;//armazena userid temporariamente para leitura
            int AuxMovieId;//armazena movieid temporariamente para leitura
            std::string s;
            //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
            getline(arq, s, ',');
            getline(arq, s, ',');
            getline(arq, s, ',');
            getline(arq, s, '\n');
            //--------------------------
            
            //LENDO O ARQUIVO E ADICIONANDO NO HASH
            for(int i = 0; i < N; i++)
            {   aleatorio = rand()%2;
                if(aleatorio==1){
                    getline(arq, s, ',');
                    AuxUserId = atoi(s.c_str());

                    getline(arq, s, ',');
                    AuxMovieId = atoi(s.c_str());

                    getline(arq, s, ',');
                    
                    getline(arq, s, '\n');
                    
                    auxDupla.setUser(AuxUserId);
                    auxDupla.setMovies(AuxMovieId);
                    tabela->inserir(auxDupla);//como saber se foi inserido ou nao?
                }else{//se nao tiver nenhum retorno vai inserir -1 elementos
                    i--;//coloca retorno no inserir boolean?
                }
            }
            cout << "colisoes " << tabela->qtdColisoes()<< endl;
            cout << "memoria: " << tabela->getPosOcupadas() << endl;
    
            vetEspaco[j-1] = tabela->getPosOcupadas();
            vetColisoes[j-1] = tabela->qtdColisoes();
            //------------------------------------------
            delete tabela;//Deletando vetor de movies
            
            arq.close();//FECHANDO O ARQUIVO DE DADOS
        }
        
    }//Fim da 5 execução de cada N
    cout << "--------------------------------------" << endl;
    //Análise dos dados para cada N

    float auxMediaEspaco = 0;
    float auxMediaColisao = 0;
    for(int i=0; i< 5; i++){
        auxMediaEspaco += vetEspaco[i];
        auxMediaColisao += vetColisoes[i];
    }
    auxMediaColisao = auxMediaColisao/5;
    auxMediaEspaco = auxMediaEspaco/5;

    saida4 << "Media de colisoes: " << auxMediaColisao << endl;
    saida4 << "Meida de memoria gasta: " << auxMediaEspaco << endl;
}


for(int i = 0; i< tam_entrada; i++){
        
    saida4 << endl << "Resultado do Duplo Hash para N = " 
    << entradas[i] << endl << endl;
    cout << endl << "Resultado do Re-hashing para N = "
    << entradas[i] << endl << endl;
    for(int j =1; j<=5; j++){//Executar 5 vezes para cada N
        cout << endl << j << " execução para N = " << entradas[i] << endl;
        srand(2*j*(i+1));//Sementes diferentes para cada execução de cada N

        arq.open("ratings.csv");

        if(arq.is_open())
        {   
            int N = entradas[i];
            DHashing* tabela = new DHashing(N);
            DuplaMovies auxDupla = DuplaMovies(); //armazena a dupla temporariamente
            //para colocar na tabela
            int AuxUserId;//armazena userid temporariamente para leitura
            int AuxMovieId;//armazena movieid temporariamente para leitura
            std::string s;
            //ALGORITMO PARA LER E DESCARTAR A PRIMEIRA LINHA
            getline(arq, s, ',');
            getline(arq, s, ',');
            getline(arq, s, ',');
            getline(arq, s, '\n');
            //--------------------------
            
            //LENDO O ARQUIVO E ADICIONANDO NO HASH
            for(int i = 0; i < N; i++)
            {   aleatorio = rand()%2;
                if(aleatorio==1){
                    getline(arq, s, ',');
                    AuxUserId = atoi(s.c_str());

                    getline(arq, s, ',');
                    AuxMovieId = atoi(s.c_str());

                    getline(arq, s, ',');
                    
                    getline(arq, s, '\n');
                    
                    auxDupla.setUser(AuxUserId);
                    auxDupla.setMovies(AuxMovieId);
                    tabela->inserir(auxDupla);//como saber se foi inserido ou nao?
                }else{//se nao tiver nenhum retorno vai inserir -1 elementos
                    i--;//coloca retorno no inserir boolean?
                }
            }
            cout << "colisoes " << tabela->qtdColisoes()<< endl;
            cout << "memoria: " << tabela->getPosOcupadas() << endl;
    
            vetEspaco[j-1] = tabela->getPosOcupadas();
            vetColisoes[j-1] = tabela->qtdColisoes();
            //------------------------------------------
            delete tabela;//Deletando vetor de movies
            
            arq.close();//FECHANDO O ARQUIVO DE DADOS
        }
        
    }//Fim da 5 execução de cada N
    cout << "--------------------------------------" << endl;
    //Análise dos dados para cada N

    float auxMediaEspaco = 0;
    float auxMediaColisao = 0;
    for(int i=0; i< 5; i++){
        auxMediaEspaco += vetEspaco[i];
        auxMediaColisao += vetColisoes[i];
    }
    auxMediaColisao = auxMediaColisao/5;
    auxMediaEspaco = auxMediaEspaco/5;

    saida4 << "Media de colisoes: " << auxMediaColisao << endl;
    saida4 << "Meida de memoria gasta: " << auxMediaEspaco << endl;
}
    
    saida4.close();//Fechando arquivo de saida
    return 0;
}
