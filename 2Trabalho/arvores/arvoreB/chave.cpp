#include "chave.h"

chave::chave()
{
    //Construtor padrao
}

//Construtor completo
chave::chave(float valor, float rating, long int timestamp){
    this->valor = valor;
    this->rating = rating;
    this->timestamp = timestamp;
}

chave::~chave()
{
    //Destrutor padrao
}

//Define o valor da chave
void chave::setValor(float valor){
    this->valor = valor;
}

//Define rating da chave
void chave::setRating(float rating){
    this->rating = rating;
}

//Define timestamp da chave
void chave::setTime(long int Time){
    this->timestamp = Time;
}

//Retorna valor da chave
float chave::getValor(){
    return this->valor;
}

//Retorna rating da chave
float chave::getRating(){
    return this->rating;
}

// Retorna timestamp da chave
long int chave::getTimeStamp(){
    return this->getTimeStamp;
}

