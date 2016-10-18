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
  bool vazia();
private:
  ListaSimples<T> *lista;
};

template<typename T>
Pilha<T>::Pilha(){
  lista = new ListaSimples<T>;
}

template<typename T>
Pilha<T>::~Pilha(){
  delete lista;
}

template<typename T>
unsigned int Pilha<T>::getQuantos(){
  return lista->getQuantos();
}

template<typename T>
T Pilha<T>::peek(){
  return lista->getPrimeiro();
}

template<typename T>
void Pilha<T>::push(T info){
  lista->adicionarComeco(info);
}

template<typename T>
T Pilha<T>::pop(){
  if (!this->vazia())
    return lista->retirarComeco();
  else
    throw std::out_of_range("Assim você arrebenta com tudo");
}

template<typename T>
bool Pilha<T>::vazia(){
  return getQuantos() == 0;
}

#endif