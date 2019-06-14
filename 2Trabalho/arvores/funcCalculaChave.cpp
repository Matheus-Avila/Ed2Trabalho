#include "arvoreB/arvoreb.h"
#include "arvoreB/chave.h"
#include "arvoreB/pagina.h"
#include <cmath>

using namespace std;

//funcao chamada no main para gerar a chave. Antes da criacao da chave (movie)
int geraChave(int userId, int movieId){

    return (userId*movieId)/2;
}