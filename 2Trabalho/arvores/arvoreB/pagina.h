#include "chave.h"

//No da arvoreB
class pagina{
    public:
    
    pagina();//Construtor padrao
    pagina(int ordem, pagina* pai);//Construtor com ordem da arvore
    ~pagina();//Destrutor
    int getPosOcupadas();//Retorna numero de chaves ocupadas
    int getOrdem();//Retorna a ordem da pagina
    bool paginaCheia();//Testa se existem chaves disponiveis na pagina(T: Cheia/ F: PosLivre)
    void subirChave(chave chaveNova, pagina* filha);//Apos o split, sobe a chave 
    // e o novo filho para o pai
    void inserirNaFolha(chave chaveNova); //Antes de inserir na folha,
    // ordena as chaves da folha, e insere o valor
    void splitPagina();//Divide a pagina lotada     
    bool eRaiz();//Testa se a página é a raiz  
    void setPai(pagina* pai);//Define o pai da pagina
    pagina* getPai();//Retorna o pai da pagina
    chave* getChave(int pos);//Retorna a chave na posicao pos
    pagina* getFilha(int pos);//Retorna a pagina filha da chave na posicao pos

    private:
    int ordem;// Ordem da arvore (sera armazenada em cada pagina)
    int posOcupadas; // Posicoes de chaves ocupadas
    chave* chaves; // Vetor de chaves iniciado com tamanho 2*ordem
    pagina** paginasFilhas; // Vetor de paginas filhas
    pagina *paginaPai; // Ponteiro para a pagina pai
    bool NoIntermediario;//Verifica se nao eh nem folha nem raiz
};