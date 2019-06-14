#include "chave.h"
#include "pagina.h"

class arvoreb{
    public:
    
    arvoreb();//Construtor padrao
    arvoreb(int ordem);//Construtor com ordem da arvore
    ~arvoreb();//Destrutor
    int getOrdem();//Retorna a ordem da arvore
    bool buscaChave(int chave); //Busca uma chave na arvore(T:existe/ F:nao existe na arvore)
    void inserirChave(chave movie, int* comparacoes, int* trocas); //Insere uma chave na arvore(F:ja existe essa chave)

    private:
    int numeroComparacoes; //Numero de comparacoes 
    int numeroTrocas; //Numero de trocas
    int ordem; //Ordem da arvore 
    pagina* raiz; // pagina raiz da arvore
};