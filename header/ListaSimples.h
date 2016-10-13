#ifndef LISTA_SIMPLES
#define LISTA_SIMPLES

template<class T>
struct NoLista{
  T info;
  struct NoLista<T>* prox;
};


template<class T>
class ListaSimples{
 public:
  unsigned int getQuantos();
  void adicionarComeco(T);
  void adicionarFinal(T);
  void percorrer(void (*f)(T));

 private:
  struct NoLista<T>* primeiro;
  struct NoLista<T>* ultimo;
  unsigned int quantos;
};

#endif
