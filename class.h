#include <iostream>
#include <string>
#include <cmath>
#include <string>


using namespace std;


class DuplaMovies{
public:
	DuplaMovies();
	DuplaMovies(long int idMovies, long int idUser);
	~DuplaMovies();
	void setMovies(long int idMovies);
	void setUser(long int idUser);
	long int getMovies();
	long int getUser();

private:
	long int idUser;
	long int idMovies;
}; 


class No{
public:
	No(); // construtor
	~No(); // destrutor
	No* retornarNoProximo(); // retorna Nó proximo
	void colocarNoProximo(No* proximo); // coloca Nó proximo
	long int retornarMovies(); // retorna idMovies inserido dentro do no
	long int retornarUser(); // retorna idUser inserido dentro do no
	void colocarDado(DuplaMovies dupla); // coloca DuplaMovies dentro do no
private:
	No* proximo; // variavel do nó próximo
	DuplaMovies* dupla; // variavel do dado
};


class Lista{
public:
	Lista(); // construtor
	~Lista(); // destrutor
	void inserir(DuplaMovies valor); // inserir um valor
	bool listaVazia(); // verificar se a lista eh vazia
	No* busca(long int valor); // busca de um valor - NULL se nao existir
	int qtdPosPercorridas(long int valor); // Retorna qtd de posicoes percorridas de um valor na lista
	No* getPrimeiro();
private:
	No* primeiro; // variavel do primeiro no da lista
    No* ultimo; // variavel do ultimo no da lista
    int tam; // variavel do tamanho da lista
};


class ESeparado{
public:
	ESeparado(int tamanho);  // inicializador
	~ESeparado(); // destrutor
	unsigned long int qtdColisoes(); // retorna qtd de colisoes
	void inserir(DuplaMovies valor); // insercao de valores
private:
	int tam; // tamanho da tabela
	Lista *tabela; // tabela de dados
	long colisoes; // quantidade de colisoes
	int funcaoHashing(DuplaMovies valor); // calcular posicao
};


class ECoalescido{
public:
	ECoalescido(int tamanho); // inicializador
	~ECoalescido(); // destrutor
	unsigned long int qtdColisoes(); // retorna qtd de colisoes
	void inserir(DuplaMovies valor); // insercao de valores
private:
	int tam; // tamanho da tabela
	long int *vetEstado; // parte da tabela com TAG estado da posicao(-2:vazio -1:fim)
	DuplaMovies* vetDupla; // parte da tabela com os movies
	long colisoes; // quantidade de colisoes
	int funcaoHashing(DuplaMovies valor); // calcular posicao
};

class SLinear{
public:
	SLinear(int tamanho);  // construtor
	~SLinear(); // destrutor
	unsigned long int qtdColisoes(); // retorna qtd de colisoes
	void inserir(DuplaMovies valor); // insercao de valores
private:
	int tam; // tamanho da tabela
	DuplaMovies* vetDupla; // vetor de movies
	long colisoes; // quantidade de colisoes
	int funcaoHashing(DuplaMovies valor); // calcular posicao
	int posOcupadas; // Numero de posicoes preenchiadas
	int* vetEstado; // parte da tabela com TAG estado da posicao(-1:vazio)
};

class SQuadratica{
public:
	SQuadratica(int tamanho); // inicializador
	~SQuadratica(); // destrutor
	unsigned long int qtdColisoes(); // retorna qtd de colisoes
	void inserir(DuplaMovies valor); // insercao de valores
private:
	int tam; // tamanho da tabela
	DuplaMovies* vetDupla; // vetor de movies
	int* vetEstado; // parte da tabela com TAG estado da posicao(-1:vazio)
	long colisoes; // quantidade de colisoes
	int funcaoHashing(DuplaMovies valor); // calcular posicao
	int posOcupadas; // Numero de posicoes preenchiadas

};

class DHashing{
public:
	DHashing(int tamanho);  // inicializador
	~DHashing(); // destrutor
	unsigned long int qtdColisoes(); // retorna qtd de colisoes
	void inserir(DuplaMovies valor); // insercao de valores
private:
	int tam; //tamanho da tabela
    DuplaMovies *vetDupla; //vetor de movies
	int* vetEstado; // parte da tabela com TAG estado da posicao(-1:vazio)
    long colisoes; // numero de comparacoes realizadas
	int funcaoHashing(DuplaMovies valor); // calcular primeira posicao
	int ReHashing(DuplaMovies valor); // calcular segunda posicao
	int posOcupadas; // numero de posicoes preenchiadas
	void inicializarTabela(); // inicializacao da tabela
};