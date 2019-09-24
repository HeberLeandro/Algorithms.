#ifndef _pilha2_H_
#define _pilha2_H_

#include <stdexcept>
#include <iostream>
using namespace std;

template <class T>
class PilhaGenerica{
	public:
		int capacidade;
		
		PilhaGenerica(int cap){
			this->capacidade = cap;
		}
		virtual ~PilhaGenerica(){}
	 	virtual void empilha(T) = 0;
	 	virtual T desempilha() = 0;
};


template <class T>
struct Node {
	T dados;
	struct Node * prox;
};

template <class T>
class PilhaEncadeada : public PilhaGenerica<T> {
	
	private:
		int Nitems; // Quantidade de N�s na pilha.
		Node<T> *topo;
		
		
	public:
		PilhaEncadeada(int capacidade) : PilhaGenerica<T>(capacidade){
			this->topo = NULL;
			this->capacidade = capacidade;
			this->Nitems = 0;		
		}
		
		~PilhaEncadeada(){
			while(this->topo != NULL){
				Node<T> *aux = this->topo;
				this->topo = this->topo->prox;
				delete aux;
			}
			delete topo;
		}
		
		void empilha(T item) {
			if(this->Nitems < this->capacidade){
				Node<T> *novoNode = new Node<T>;
				novoNode->dados = item;
				novoNode->prox = this->topo;
				this->topo = novoNode;	
				this->Nitems++;
			}else{
				throw overflow_error("Overflow");
			}
		}
		
		T desempilha(){
			if(this->Nitems > 0){
				Node<T> *aux = this->topo;
				this->topo = this->topo->prox;
				this->Nitems--;			
				return aux->dados;
			}else {
				throw underflow_error("Underflow");
			}
		}
};

template <class T>
class PilhaArray : public PilhaGenerica<T> {
	
	private:
		int  topo;
		T * items;
		
	public:
		PilhaArray(int capacidade) : PilhaGenerica<T>(capacidade){
			this->items = new T[capacidade];
			this->topo =  -1;
			this->capacidade = capacidade;		
		}
		
		~PilhaArray(){
			delete [] items;
		}
		
		void empilha(T item) {
			if(this->topo < this->capacidade-1){
				this->topo += 1;	
				this->items[this->topo] = item;
			
			}else{
				throw overflow_error("Overflow");
			}
		}
		
		T desempilha(){
			if(this->topo >= 0){
				int aux = this->topo;
				this->topo -= 1;			
				return this->items[aux];
			}else {
				throw underflow_error("Underflow");
			}
		}
};

#endif

