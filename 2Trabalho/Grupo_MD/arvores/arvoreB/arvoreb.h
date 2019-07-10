#ifndef _arvoreb_H_
#define _arvoreb_H_
#include "pagina.h"

class arvoreb{
    public:
    
    arvoreb();//Construtor padrao
    arvoreb(int ordem);//Construtor com ordem da arvore
    ~arvoreb();//Destrutor
    int getOrdem();//Retorna a ordem da arvore
    bool buscaChave(int chave, int* comparacoes, int* trocas); //Busca uma chave na arvore(T:existe/ F:nao existe na arvore)
    void inserirChave(chave* movie, int* comparacoes, int* trocas); //Insere uma chave na arvore(F:ja existe essa chave)
    int numeroComparacoes; //Numero de comparacoes 
    int numeroTrocas; //Numero de trocas

    private:
    int ordem; //Ordem da arvore 
    pagina* raiz; // pagina raiz da arvore
};
#endif