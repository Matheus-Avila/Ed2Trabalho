#include "chave.h"

chave::chave()
{
    //Construtor padrao
}

chave::chave(int valor, float rating, long int timestamp){
    this->valor = valor;
    this->rating = rating;
    this->timestamp = timestamp;
}
chave::~chave()
{
    //Destrutor padrao
}

void chave::setValor(int valor){
    this->valor = valor;
}

void chave::setRating(float rating){
    this->rating = rating;
}
void chave::setTime(long int Time){
    this->timestamp = Time;
}

int chave::getValor(){
    return this->valor;
}

float chave::getRating(){
    return this->rating;
}

long int chave::getTimeStamp(){
    return this->getTimeStamp;
}

