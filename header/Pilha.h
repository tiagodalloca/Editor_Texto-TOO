#ifndef PILHA
#define PILHA

#include "ListaSimples.h"

template<typename T>
class Pilha{
public:
  Pilha();
  ~Pilha();
  unsigned int getQuantos();
  T getTopo();
  T pop();
  void push(T info);
private:
  ListaSimples<T> lista;
};

template<typename T>
Pilha<T>::Pilha(){
  lista = ListaSimples<T>();
}

template<typename T>
Pilha<T>::~Pilha(){
  delete lista;
}

template<typename T>
unsigned int Pilha<T>::getQuantos(){
  return lista.getQuantos();
}

template<typename T>
T Pilha<T>::getTopo(){
  return lista.getPrimeiro();
}

template<typename T>
void Pilha<T>::push(T info){
  lista.adicionarComeco();
}

template<typename T>
T Pilha<T>::pop(){
  return lista.retirarComeco();
}

#endif
