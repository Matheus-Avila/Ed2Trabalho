#include "chave.h"

//No da arvoreB
class pagina{
    public:
    
    pagina();//Construtor padrao
    pagina(int ordem);//Construtor com ordem da arvore
    ~pagina();//Destrutor
    int getPosOcupadas();//Retorna numero de chaves ocupadas
    bool paginaCheia();//Testa se existem chaves disponiveis na pagina(T: Cheia/ F: PosLivre)
    void splitPagina();//Divide a pagina cheia se tentar inserir
    void eRaiz();//Testa se a página é a raiz  
    //Duvida!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    void setPai(pagina* pai);//Define o pai de uma pagina ///// Precisa mesmo dessa funcao?????
    chave* getChave(int pos);//Retorna a chave na posicao pos
    pagina* getFilha(int pos);//Retorna a pagina filha da chave na posicao pos

    private:
    void ordenaPagina(); // Após inserir um valor, ordena as chaves da pagina
    int posOcupadas; // Posicoes de chaves ocupadas
    chave* chaves; // Vetor de chaves iniciado com tamanho 2*ordem
    pagina* paginasFilhas; // Vetor de paginas filhas  
    //Duvida!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //Escolha um dos dois
    pagina *paginaPai; // Ponteiro para a pagina pai
    //chave *paiChave; // Ponteiro para a chave pai
    //Duvida****************************************
    bool NoIntermediario;//Verifica se nao eh nem folha nem raiz
};