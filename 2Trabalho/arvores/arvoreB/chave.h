#include <string>
#include <iostream>
//Removido por causa do erro: "chave.h include itself"
//#include "pagina.h"

class chave
{
    public:

    chave(); //Construtor padrão
    chave(int valor, float rating, long int timestamp); //Construtor completo
    ~chave(); //Destrutor
    void setValor(int valor); //Define valor da chave
    void setRating(float rating); //Define rating da chave
    void setTime(long int timestamp); //Define timestamp da chave
    int getValor(); //Retorna valor da chave
    float getRating(); //Retorna rating da chave
    long int getTimeStamp(); // Retorna timestamp da chave
    
    private:
    int valor; //Chave para busca
    float rating; //Rating da chave
    long int timestamp; //TimeStamp da chave
    

};