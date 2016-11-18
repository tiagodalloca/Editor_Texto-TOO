#ifndef PILHA
#define PILHA

#include "ListaSimples.h"

template<typename T>
class Pilha{
public:
  Pilha();
  ~Pilha();
  unsigned int getQuantos();
  T peek();
  T pop();
  void push(T info);
  void esvaziar();
  bool vazia();
private:
  ListaSimples<T> lista;
};

template<typename T>
Pilha<T>::Pilha(){
  lista = ListaSimples<T>();
}

template<typename T>
Pilha<T>::~Pilha(){
}

template<typename T>
unsigned int Pilha<T>::getQuantos(){
  return lista.getQuantos();
}

template<typename T>
T Pilha<T>::peek(){
  return lista.getPrimeiro();
}

template<typename T>
void Pilha<T>::push(T info){
  lista.adicionarComeco(info);
}

template<typename T>
T Pilha<T>::pop(){
  if (!this->vazia())
    return lista.retirarComeco();
  else
    throw "Underflow";
}

template<typename T>
void Pilha<T>::esvaziar(){
  lista.esvaziar();
}

template<typename T>
bool Pilha<T>::vazia(){
  return lista.getQuantos() == 0;
}

#endif
