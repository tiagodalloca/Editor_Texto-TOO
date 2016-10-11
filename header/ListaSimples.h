#ifndef ListaSimples
#define ListaSimples

template<class T>
struct NoLista{
  T info;
  struct *NoLista prox;
}

class ListaSimples{
 public:
  unsigned int quantos();
  void adicionarComeco(T);
  void adicionarFinal(T);
  void percorrer(void (*f)(T));

 private:
  struct *NoLista primeiro;
  struct *NoLista ultimo;
  unsigned int quantos;
};

#endif
