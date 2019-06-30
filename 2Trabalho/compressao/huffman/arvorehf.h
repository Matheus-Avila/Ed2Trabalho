#include <vector>
#include "nohf.h"
#include <string>

class arvorehf{

    public:
    arvorehf();//Construtor padrao
    ~arvorehf();
    void montarArvore(string texto);//Monta a arvore de huffman para o texto
    vector<int> codifica(string texto);
    string decodifica(string);
    
    private:
    int size;
    vector<nohf> arvoreTabela;//Tabela com as frequencias dos
    //caracteres que sera usado para montar a arvore de huffman
};