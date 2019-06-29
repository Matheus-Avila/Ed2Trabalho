#include <vector>
#include "nohf.h"
#include <string>

class arvorehf{

    public:
    arvorehf();//Construtor padrao
    ~arvorehf();
    void montarArvore(string texto);//Monta a arvore de huffman para o texto
    int* codifica(string texto);
    string decodifica(string);

    private:

    vector<nohf> arvore;//Vetor com a logica para montar a arvore de huffman
};