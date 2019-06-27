
#include <iostream>
#include <fstream>
#include "./tela.h"

using namespace std;

//le userid e movieId
//auxChave = GerarChave(userid, movie id)
//if(buscaChave(auxChave))
    //procura outro movie para inserir
//else
    //c = new Chave(auxChave, m.rating, m.timestamp)
    //inserirChave(c)

void troca(int* a, int* b){
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
    *a = *a+2;
    *b = *b+2;
}

int main()
{   
    switch (2){
    case 1:
        float *a = new float;
        *a = 10.5; 
        break;
    case 2:
        int *a = new int; 
        *a = 10;
    default:
        char *a = new char;
        *a = 'c';
        break;
    }   
    cout << *a;
    /* int a= 0, b=5;
    troca(&a, &b);
    cout << a << " " << b;

    int ** vet = new int*[10];
    int ** bet = new int*[10];
    int ** fim = new int*[10];
    int aux = 0;
    cout << "sd";
    for(int i = 0; i < 10; i++){

        vet[i] = &i;
        aux = 10*i;
        bet[i] = &aux;
    }

    for(int i = 0; i < 10; i++){
        cout << *vet[i] << "         " << *bet[i] << endl;
    }

    for(int i = 0; i < 10; i++){
        fim[i] = bet[i];
        if(i<5){
            fim[i] = vet[i];
        }
    }

    for(int i = 0; i < 10; i++){
        cout << *fim[i]  << endl;
    }*/
    return 0;
}