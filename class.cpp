#include "class.h"
#include <iostream>
#include <string>
#include <cmath>
#include <string>

//No implementação

// Construtor
No::No(){
    this->proximo = NULL;
}

// Destrutor
No::~No(){}

// Retorna Nó proximo
No* No::retornarNoProximo(){
    return proximo;
}

// Coloca Nó proximo
void No::colocarNoProximo(No* p){
    this->proximo = p;
}

// Retorna idMovies inserido dentro do no
long int No::retornarMovies(){
    return this->dupla->getMovies();
}

// Retorna idUser inserido dentro do no
long int No::retornarUser(){
    return this->dupla->getUser();
}
// Coloca Movies dentro do no
void No::colocarDado(DuplaMovies dupla){
    this->dupla = new DuplaMovies(dupla.getMovies(), dupla.getUser());
}


//Fim No 

//Dupla Movies implementação

DuplaMovies::DuplaMovies(){}

DuplaMovies::DuplaMovies(long int idMovies, long int idUser){
	this->idMovies = idMovies;
	this->idUser = idUser;
}

//Destrutor
DuplaMovies::~DuplaMovies(){}

//Define idMovies
void DuplaMovies::setMovies(long int idMovies){
	this->idMovies = idMovies;
}

//Define idUser
void DuplaMovies::setUser(long int idUser){
	this->idUser = idUser;
}

//Retorna idMovies
long int DuplaMovies::getMovies(){
	return this->idMovies;
}

//Retorna idUser
long int DuplaMovies::getUser(){
	return this->idUser;
}

//Fim Dupla Movies

//Lista implementação

//Atribui o primeiro e o último nó da lista como NULL e o tamanho com zero.
Lista::Lista(){
	this->primeiro = NULL;
	this->ultimo = NULL;
	this->tam = 0;
}

// Destrutor
Lista::~Lista(){
    No* p = this->primeiro;
    while(p != NULL){
        No* t = p->retornarNoProximo();
        delete p;
        p = t;
    }
}

// Inserir um valor na lista. Insere no final da lista.
void Lista::inserir(DuplaMovies valor){
	
	
	No* novo = new No();
	novo->colocarDado(valor);

	if(this->listaVazia()){
		this->primeiro = novo;
		this->ultimo = novo;
	}else{
		novo->colocarNoProximo(this->ultimo);
		this->ultimo = novo;
	}
	this->tam++;
}


//Retorna se a lista é vazia ou não
bool Lista::listaVazia(){
	return (this->primeiro == NULL);
}

//Retorna o primeiro no da lista
No* Lista::getPrimeiro(){
	return primeiro;
}

/*
// Busca de um valor na lista
No* Lista::busca(long int valor){
	if(this->listaVazia()){
		return NULL;
	}else{
		No* busca = new No();
		busca = this->primeiro;
		while(busca->retornarNoProximo() != NULL){
			if(busca->retornarDado() == valor){
				return busca;
			}
			busca = busca->retornarNoProximo();
		}
		return NULL;
	}
}*/
/*
// Retorna qtd de posicoes percorridas de um valor na lista
int Lista::qtdPosPercorridas(long int valor){
	if(this->listaVazia()){
		return -1;
	}else{
		int qtd = 0; // contador de quantidade
		No* busca = new No();
		busca = this->primeiro;
		while(busca->retornarNoProximo() != NULL){
			if(busca->retornarDado() == valor){
				return qtd;
			}
			qtd++;
			busca = busca->retornarNoProximo();
		}
		return -1;
	}
}*/


//Fim lista

//ESeparado implementação

// Construtor da classe.
ESeparado::ESeparado(int tamanho)
{
	// alocacao das variaveis
	this->tam = tamanho;
    this->tabela = new Lista[tam];
    this->colisoes = 0;
}

// Destrutor da classe.
ESeparado::~ESeparado(){
    delete []this->tabela;
}

// Retorna a quantidade de comparações.
unsigned long int ESeparado::qtdColisoes() {
    return this->colisoes;
}

// Insercao de valores, alem do calculo de colisoes
void ESeparado::inserir(DuplaMovies valor){
    int posicao = funcaoHashing(valor); // calcula a posicao atraves da funcao de hashing.

	// A insercao de valores eh no final da lista
	if(!this->tabela[posicao].listaVazia()){
		//Teste para não inserir dois movies com os mesmos idUser e idMovies
		int testaIguais = 0;
		No* busca = this->tabela[posicao].getPrimeiro();
		while(busca != NULL){
			if(valor.getMovies() == busca->retornarMovies() &&
			 valor.getUser() == busca->retornarUser()){
				testaIguais = 1;
				break;
			}
			busca = busca->retornarNoProximo();
		}
		if(testaIguais == 0){
        	colisoes++;
			this->tabela[posicao].inserir(valor); // insere o valor na lista que esta relacionada na tabela
		}
    }else{
		this->tabela[posicao].inserir(valor); // insere o valor na lista que esta relacionada na tabela
	}
}

//Calcula a posição de cada valor. Função hashing de divisão.
int ESeparado::funcaoHashing(DuplaMovies valor){
    int resultado = (valor.getUser() + valor.getMovies())%this->tam;
	return resultado;
}


// Construtor da classe.
ECoalescido::ECoalescido(int tamanho)
{
	// alocacao das variaveis e inicializacao da tabela
	this->tam = tamanho;
    this->colisoes = 0;
    this->vetEstado = new long int [tam];
    this->vetDupla = new DuplaMovies [tam];
	for(int i=0; i < this->tam; i++){
		this->vetEstado[i] = -2;//A posicao 1 indica colisao (na inicializacao é -2)
	}
}

// Destrutor da classe.
ECoalescido::~ECoalescido(){
    delete []vetEstado;
    
    delete []vetDupla;
}

// Retorna a quantidade de comparações.
unsigned long int ECoalescido::qtdColisoes() {
    return this->colisoes;
}

//Método para inserir o valor na tabela.
void ECoalescido::inserir(DuplaMovies valor){
	int posicao = funcaoHashing(valor); // Calcula a posicao pela funcao hashing.

	// Se estiver vazia, apenas coloque valor e atualiza o FLAG (-1)
	if(this->vetEstado[posicao] == -2){
		this->vetDupla[posicao] = valor;
		this->vetEstado[posicao] = -1;
	}else{ // Caso contrário, verifica se teve mais números colididos para atualizar o indice.
		int aux; // auxiliar para a nova posicao
		int anterior = posicao; // auxiliar para colocar o numero o que será referenciado caso ocorra a colisao.

		// Caso seja (-1), tal numero e o final daquela posicao, basta verificar alguma posicao vazia a partir do final.
		if(this->vetEstado[posicao] == -1){
			aux = tam-1;
			colisoes++;
		}else{ // Caso contrario, percorrer a cadeia e verificar até chegar a FLAG (-1) e a partir dai verificar posicao vazia.
			aux = posicao;
			long proximo;
			while(this->vetEstado[aux] != -1){
				colisoes++;
				anterior = aux;
				proximo = this->vetEstado[aux];
				aux = (int) proximo;
			}
		}

		// Verifica indice de tabela vazia até quando achar uma ou acaba de percorrer toda a tabela.
		while(this->vetEstado[aux] != -2){
			colisoes++;
			aux--;
			if(aux == -1){//Indice invalido. Chegou no final da tabela e não tinha posição livre
				break;
			}
		}

		// Caso o índice for -1, nenhuma posicao da tabela esta disponível.
		if(aux == -1){
			cout << "Tabela Cheia!!" << endl;
		}else{ // Caso contrario, atualiza os índices envolvidos e coloca o valor no vetor.
			this->vetEstado[anterior] = aux;
			this->vetEstado[aux] = -1;
			this->vetDupla[aux] = valor;
		}
	}
}

//Calcula a posição de cada valor. Função hashing de divisão.
int ECoalescido::funcaoHashing(DuplaMovies valor){
    int resultado = (valor.getUser() + valor.getMovies())%this->tam;
	return resultado;
}
//Fim ECoalescido

//Sondagem linear

// Construtor da classe.
SLinear::SLinear(int tamanho)
{
	// alocacao das variaveis e inicializacao da tabela
    this->tam = tamanho;
    this->vetDupla = new DuplaMovies[tam];
	this->vetEstado = new int[tam];
	this->colisoes = 0;
    this->posOcupadas = 0;
	//Inicializar a tabela, ou seja, preencher todas as posi��es com -1 (vazio).
	for(int i=0; i < this->tam; i++){
        this->vetEstado[i] = -1;
	}
}

// Destrutor da classe.
SLinear::~SLinear(){
    delete []this->vetDupla;
    delete []this->vetEstado;
}

// Retorna a quantidade de compara��es.
unsigned long int SLinear::qtdColisoes(){
    return this->colisoes;
}

// Insercao de valores, alem do calculo de colisoes
void SLinear::inserir(DuplaMovies valor){
    int posicao = funcaoHashing(valor); // Calcula a posicao pela funcao hashing.
    if(posOcupadas >= this->tam){
        cout << "Tabela cheia" << endl; // Imprime tabela cheia caso as posicoes vazias se esgotem
    }else{
		// Enquanto nao acha posicao vazia, acumula as colisoes e ira para a proxima posicao
        while(this->vetEstado[posicao] != -1){
            colisoes++;
            posicao++;

			// Caso chegue na ultima posicao, reinicia a contagem;
			if(posicao >= tam){
                posicao = 0;
            }
        }
        this->vetDupla[posicao] = valor; // caso encontrada posicao livre, inserir valor na tabela
        posOcupadas++;  // atualizar posicoes posOcupadas
    }
}

//Calcula a posicao de cada valor. Funcao hashing de divisao
int SLinear::funcaoHashing(DuplaMovies valor){
	int resultado = (valor.getUser() + valor.getMovies())%this->tam;
	return resultado;
}

//Fim sondagem linear

//Sondagem quadrática

// Construtor da classe.
SQuadratica::SQuadratica(int tamanho)
{
	// alocacao das variaveis e inicializacao da tabela
    this->tam = tamanho;
    this->vetEstado = new int[tam];
    this->vetDupla = new DuplaMovies[tam];
    this->posOcupadas = 0;
	this->colisoes = 0;
	//Inicializar a tabela, ou seja, preencher todas as posicoes com -1 (vazio).
	for(int i=0; i < this->tam; i++){
        this->vetEstado[i] = -1;
    }
}

// Destrutor da classe.
SQuadratica::~SQuadratica(){
	delete []this->vetEstado;
	delete []this->vetDupla;
}

// Retorna a quantidade de compara��es.
unsigned long int SQuadratica::qtdColisoes(){
    return this->colisoes;
}

// Insercao de valores, alem do calculo de colisoes
void SQuadratica::inserir(DuplaMovies valor){// Calcula a posicao pela funcao hashing.
    if(posOcupadas > this->tam){               // Imprime tabela cheia caso as posicoes vazias se esgotem
        cout << "Tabela cheia" << endl;
    }else{
        int posicao = funcaoHashing(valor);
        long int calculoPos = 0;
        int auxColisao = 0; /// contador - colisoes que ocorreu para colocar um valor.
        int i = 0; /// contador - calculo para a proxima posicao caso ocorra colisao

		// Se não achar uma posicao após verificar 40% do tamanho da tabela de colisoes 
		//ele para de verificar e utiliza sondagem linear.
		while(this->vetEstado[posicao] != -1 && auxColisao < this->tam*0.4){
            colisoes++;
            i++;
            auxColisao++;
            calculoPos = posicao + i*i;

			// Caso chegue no fim da tabela, reinicie os contadores referentes a posicao
            if(this->tam <= calculoPos){
                calculoPos = 0;
                i = 0;
                posicao = 0;
            }else{
                posicao = calculoPos;
            }
        }

        if(auxColisao > this->tam*0.4){
			posicao = 0;
			while(this->vetEstado[posicao] != -1){
				posicao++;
				colisoes++;
			}
        }

        this->vetDupla[posicao] = valor; // caso encontrada posicao livre, inserir valor na tabela
        posOcupadas++;   // atualizar posicoes preenchidas
    }
}

//Calcula a posicao de cada valor. Funcao hashing de divisao.
int SQuadratica::funcaoHashing(DuplaMovies valor){
	int resultado = (valor.getMovies()+ valor.getUser())%this->tam;
	return resultado;
}
//Fim do SQuadratica

//Re-hashing

// Construtor da classe.
DHashing::DHashing(int tamanho)
{
	// alocacao das variaveis e inicializacao da tabela
	this->tam = tamanho;
    this->vetEstado = new int[tam];
	this->vetDupla = new DuplaMovies[tam];
    this->posOcupadas = 0;
    this->colisoes = 0;
	this->inicializarTabela();
}

// Destrutor da classe.
DHashing::~DHashing(){
    delete []vetDupla;
    delete []vetEstado;
}

// Retorna a quantidade de comparações.
unsigned long int DHashing::qtdColisoes() {
	return this->colisoes;
}

// Insercao de valores, alem do calculo de colisoes
void DHashing::inserir(DuplaMovies valor){
	int posicao = funcaoHashing(valor);  // Calcula a posicao pela funcao hashing.
	int auxColisoes = 0; // Variavel que guarda a quantidade de colisoes ja ocorridas
	if(posOcupadas > this->tam)
		cout << "Tabela cheia" << endl; // Imprime tabela cheia caso as posicoes vazias se esgotem
	else{

		// Se não achar uma posicao após verificar 40% do tamanho da tabela de colisoes 
		//ele para de verificar e utiliza sondagem linear.
		while(this->vetEstado[posicao] != -1 && auxColisoes < this->tam*0.4)
		{
			colisoes++;
			auxColisoes++;
			posicao = abs(posicao + auxColisoes*ReHashing(valor))%tam;
			// Caso a tabela ainda tenha posicoes livres e enquanto a posicao atual nao estiver vazia,
			//Aumentar o numero de colisoes e recalcular a nova posicao
		}
		if(auxColisoes > this->tam*0.4)
		{
			posicao = 0;
			while(this->vetEstado[posicao] != -1){
				posicao++;
			}
		}
		this->vetDupla[posicao] = valor;    // caso encontrada posicao livre, inserir valor na tabela
		posOcupadas++; // atualizar posicoes posOcupadas
	}
}

//Calcula a primeira posição de cada valor. Função hashing de divisão.
int DHashing::funcaoHashing(DuplaMovies valor){
	int resultado = (valor.getMovies() + valor.getUser())%this->tam;
	return resultado;
}

//Calcula a segunda posição de cada valor.
//Funcao hashing de divisao adaptada: eh menor e nunca sera valor nulo.
int DHashing::ReHashing(DuplaMovies valor)
{
	int resultado = ((valor.getMovies() + valor.getUser())%(this->tam-2))+1;
	return resultado;
}

//Inicializar a tabela, ou seja, preencher todas as posições com -1 (vazio).
void DHashing::inicializarTabela(){
	for(int i=0; i < this->tam; i++){
		this->vetEstado[i] = -1;
	}
}