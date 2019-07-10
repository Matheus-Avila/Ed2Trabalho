#ifndef _arvorehf_H_
#define _arvorehf_H_
#include <vector>
#include "nohf.h"
#include <string>

class arvorehf{

    public:
    arvorehf();//Construtor padrao
    ~arvorehf();
    void montarArvore(std::string texto);//Monta a arvore de huffman para o texto
    std::vector<int> codifica(std::string texto);
    std::string decodifica(std::string);
    
    private:
    int size;// Numero de folhas na arvore de Huffman
    std::vector<nohf> arvoreTabela;//Tabela com as frequencias dos
    //caracteres que sera usado para montar a arvore de huffman
};
#endif