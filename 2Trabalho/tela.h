#include "arvores/arvoreB/arvoreb.h"
#include "arvores/arvoreB/chave.h"
#include "arvores/arvoreB/pagina.h"
#include "arvores/arvoreVP/arvoreVP.h"
#include "arvores/arvoreVP/no.h"

class tela{

    public:
    tela();
    ~tela();
    void exibeMenu();//Inicia o menu
    float calculaChave();//chave usada nas arvores
    
    private:
    int* lerEntrada();//le e fecha o arquivo de entrada
    void leituraRatingsB(int* entradas, int menu);//leitura do ratings para arvoreB
    void leituraRatingsVP(int* entradas);//leitura do ratings para arvoreVP
    void leituraOverview(int* entradas, int menu);//leitura do metadata
    
};