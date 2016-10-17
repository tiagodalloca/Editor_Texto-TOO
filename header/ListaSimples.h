#ifndef LISTA_SIMPLES
#define LISTA_SIMPLES

template<class T>
struct NoLista{
  T info;
  struct NoLista<T> *prox;
};


template<typename T>
class ListaSimples{

public:
  ListaSimples();
  ~ListaSimples();
  ListaSimples(const ListaSimples<T> *l);
  unsigned int getQuantos() const;
  void adicionarComeco(T);
  void adicionarFinal(T);
  T retirarComeco();
  T retirarFinal();
  T getPrimeiro() const;
  T getUltimo() const;
  void percorrer(void (*f)(T)) const;
 protected:
  struct NoLista<T> *primeiro;
  struct NoLista<T> *ultimo;
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
  while(atual != NULL){
    struct NoLista<T> *aux;
    aux = atual;
    atual = atual->prox;
    delete aux;
  }
}

template<typename T>
ListaSimples<T>::ListaSimples(const ListaSimples<T> *l){
  struct NoLista<T> *atual;
  atual = l->primeiro;
  while(atual != NULL){
    adicionarFinal(atual->info);
    atual = atual->prox;
  }
}


template<typename T>
unsigned int ListaSimples<T>::getQuantos() const{
  return quantos;
}

template<typename T>
void ListaSimples<T>::adicionarComeco(T info){
  struct NoLista<T> *no = new NoLista<T>();
  no->info = info;
  no->prox = primeiro;
  primeiro = no;
  if (ultimo == NULL)
    ultimo = primeiro;
  quantos++;
}

template<typename T>
void ListaSimples<T>::adicionarFinal(T info){
  if (ultimo == NULL)
    adicionarComeco(info);
  else{
    struct NoLista<T> *no = new NoLista<T>();
    no->info = info;
    ultimo->prox = no;
    ultimo = no;
  }
  quantos++;
}

template<typename T>
T ListaSimples<T>::retirarComeco(){
  if (primeiro != NULL){
    struct NoLista<T> *aux;
    aux = this->primeiro;
    this->primeiro = this->primeiro->prox;
    T ret = aux->info;
    delete aux;
    quantos--;
    return ret;
  }
  else
    throw std::out_of_range("underflow");
}

template<typename T>
T ListaSimples<T>::retirarFinal(){
  if (ultimo != NULL){
    struct NoLista<T> *atual;
    struct NoLista<T> *anterior;
    atual = primeiro;
    while(atual != ultimo){
      anterior = atual;
      atual = atual->prox;
    }
    // atual vai ser último
    // anterior vai ser antepenúltimo
    T ret = atual->info;
    ultimo = anterior;
    ultimo->prox = NULL;
    anterior = NULL;
    delete atual;
    quantos--;
    return ret; 
  }
  else
    throw std::out_of_range("underflow");
}

template<typename T>
T ListaSimples<T>::getPrimeiro() const{
  return this->primeiro->info;
}

template<typename T>
T ListaSimples<T>::getUltimo() const{
  return this->ultimo->info;  
}

template<typename T>
void ListaSimples<T>::percorrer(void(*f)(T)) const{
  struct NoLista<T> *atual;
  atual = primeiro;
  while (atual != ultimo){
    f(atual->info);
    atual = atual->prox;
  }
  f(atual->info);
}
  
  
#endif
