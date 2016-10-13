#include "ListaSimples.h"

using namespace std;

ListaSimples::ListaSimples(){
  this.primeiro = NULL;
  this.ultimo = NULL;
  this.quantos = 0;
}

unsigned int ListaSimples::getQuantos(){
  return this.quantos;
}

template<class T>
void ListaSimples::adicionarComeço(T info){
  struct NoLista *no = new NoLista;
  *no->info = T;
  *no->prox = this.primeiro;
  this.primeiro = no;
}

template<class T>
void ListaSimples::adicionarFinal(T info){
  struct NoLista *no = new NoLista;
  *no->info = T;
  this.*ultimo->prox = no;
}
 

template<class T>
void ListaSimples::percorrer(void(*f)(T)){
  struct NoLista *atual = new NoLista;
  while (atual != this.ultimo){
    *f(*atual->info);
    atual = *atual->prox;
  }
}
