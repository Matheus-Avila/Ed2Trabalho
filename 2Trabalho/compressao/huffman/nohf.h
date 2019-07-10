#ifndef _nohf_H_
#define _nohf_H_

class nohf{

    public:
    
    nohf();//Construtor padrao
    nohf(char c);//Construtor completo
    ~nohf();//Destrutor padrao
    bool temPai();//Se nao tem pai eh candidato a entrar na arvore
    char getCaractere();//Retorna o caractere
    int getFrequencia();//Retorna a frequencia
    void addFrequencia();//Aumenta a frequencia
    void setFilhoEsq(int i);//Define o filho a esquerda
    int getFilhoEsq();//Retorna o filho a esquerda
    void setFilhoDir(int i);//Define o filho a direita
    int getFilhoDir();//Retorna o filho a direita
    void setPai(int i);//Define o pai
    int getPai();//Retorna o pai
    void setFrequencia(int i);//Define a frequencia

    private:
    
    char caractere;//Um dos caracteres existentes no texto
    int frequencia;//Frequencia do caractere no texto
    int pai;//No pai
    int filhoEsq;//Filho esquerdo
    int filhoDir;//Filho direita
    

};
#endif