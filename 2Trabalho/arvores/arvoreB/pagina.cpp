#include <iostream>
#include <string>
#include <cmath>
#include "pagina.h"

using namespace std;

pagina::pagina(){
    //Construtor padrao
}

pagina::pagina(int ordem){
    
}

pagina::~pagina(){
    //Destrutor
}

chave* pagina::getChave(int pos){
    return &chaves[pos];
}

pagina* pagina::getFilha(int pos){
    return &paginasFilhas[pos];
}