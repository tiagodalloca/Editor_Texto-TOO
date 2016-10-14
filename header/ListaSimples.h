#ifndef LISTA_SIMPLES
#define LISTA_SIMPLES

template<class T>
struct NoLista{
  T info;
  struct NoLista<T>* prox;
};


template<typename T>
class ListaSimples{

public:
  ListaSimples();
  ~ListaSimples();
  unsigned int getQuantos();
  void adicionarComeco(T);
  void adicionarFinal(T);
  T retirarComeco();
  T retirarFinal();
  T getPrimeiro();
  T getUltimo();
  void percorrer(void (*f)(T));
 private:
  struct NoLista<T>* primeiro;
  struct NoLista<T>* ultimo;
  unsigned int quantos;
};

template<typename T>
ListaSimples<T>::ListaSimples(){
  primeiro = NULL;
  ultimo = NULL;
  quantos = 0;
}

template<typename T>
ListaSimples<T>::~ListaSimples(){
  struct NoLista<T> *atual;
  atual = primeiro;
  while(*atual != *ultimo){
    struct NoLista<T> *aux;
    aux = atual;
    atual = *atual->prox;
    delete aux;
  }
}

template<typename T>
unsigned int ListaSimples<T>::getQuantos(){
  return quantos;
}

template<typename T>
void ListaSimples<T>::adicionarComeco(T info){
  struct NoLista<T> *no = new NoLista<T>(info, primeiro);
  primeiro = no;
  if (ultimo == NULL)
    ultimo = primeiro;
}

template<typename T>
void ListaSimples<T>::adicionarFinal(T info){
  if (ultimo == NULL)
    adicionarComeco(info);
  else{
    struct NoLista<T> *no = new NoLista<T>(info, NULL);
    *ultimo->prox = no;
  }
}

template<typename T>
T ListaSimples<T>::retirarComeco(){
  if (primeiro == NULL){
    struct NoLista<T> *aux;
    aux = this->primeiro;
    this->primeiro = this->*primeiro->prox;
    T ret = *aux->info;
    delete aux;
    return ret;
  }
  else
    return 0;
}

template<typename T>
T ListaSimples<T>::retirarFinal(){
  if (ultimo != NULL){
    struct NoLista<T> *atual;
    struct NoLista<T> *anterior;
    atual = primeiro;
    while(*atual != *ultimo){
      anterior = atual;
      atual = *atual->prox;
    }
    // atual vai ser último
    // anterior vai ser antepenúltimo
    T ret = *atual->info;
    delete atual;
    this->ultimo = anterior;
    return ret; 
  }
  else
    return 0;
}

template<typename T>
T ListaSimples<T>::getPrimeiro(){
  return this->*primeiro->info;
}

template<typename T>
T ListaSimples<T>::getUltimo(){
  return this->*ultimo->info;  
}

template<typename T>
void ListaSimples<T>::percorrer(void(*f)(T)){
  struct NoLista<T> *atual;
  atual = primeiro;
  while (*atual != *ultimo){
    *f(*atual->info);
    atual = *atual->prox;
  }
}
  
  
#endif
