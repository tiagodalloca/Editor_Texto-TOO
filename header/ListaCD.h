#ifndef LISTACD_H
#define LISTACD_H
#include "String.h"



template<class Dado>
class ListaCD
{
    struct NoLista{
    Dado info;
    struct NoLista *prox;
    struct NoLista *ant;
    };

    public:
        ListaCD();
        ~ListaCD();
        ListaCD(const ListaCD& other);
        ListaCD operator=(const ListaCD& other);
        void insiraNoComeco(Dado novo);
        void insiraNoMeio(Dado novo);
        void insiraNoFim(const Dado &novo);
        void insira(Dado novo);
        void insiraDepois(Dado novo);
        void remova();
        void removaDepois();
        Dado infoAtual();
        void avance();
        void retroceda();
        int getPos();
        bool estaVazia();
        void printarLista();
        void adicionarFinal(const Dado info);
        void adicionarComeco(const Dado info);
        Dado getPrimeiro() const;

    protected:

    private:
        int posAtual = 0;
        int quantosNos = 0;
        NoLista *primeiro;
        NoLista *ultimo;
};

template <class Dado>
ListaCD<Dado>::ListaCD()
{
    primeiro = ultimo = NULL;
}


template <class Dado>
ListaCD<Dado>::~ListaCD()
{
    if(primeiro)
        delete[] primeiro;
    if(ultimo)
        delete[] ultimo;

}

template<class Dado>
void ListaCD<Dado>::adicionarComeco(const Dado info){
  struct NoLista *no = new NoLista;
  no->info = info;
  no->prox = primeiro;
  primeiro = no;
  if (ultimo == NULL)
    ultimo = primeiro;
  quantosNos++;
}

template<class Dado>
void ListaCD<Dado>::insiraNoComeco(Dado novoDado)
{
    struct NoLista* aux = new NoLista;
    aux->info = novoDado;
    if (estaVazia())
    {
    ultimo = primeiro = aux;
    }

    aux->prox = primeiro;
    aux->ant = ultimo;
    primeiro->ant = aux;
    ultimo->prox = aux;
    primeiro = aux;
    quantosNos++;

}

template<class Dado>
Dado ListaCD<Dado>::getPrimeiro() const{
  return this->primeiro->info;
}


template<class Dado>
void ListaCD<Dado>::adicionarFinal(const Dado info){
  if (ultimo == NULL)
    adicionarComeco(info);
  else{
    struct NoLista *no = new NoLista;
    no->info = info;
    ultimo->prox = no;
    ultimo = no;
  }
  quantosNos++;
}


template <class Dado>
void ListaCD<Dado>::insiraNoFim(const Dado &novoDado)
{
    if (estaVazia())
    {
        insiraNoComeco(novoDado);
    }
    else
    {
        struct NoLista* aux = new NoLista;
        aux->info = novoDado;
        ultimo->prox = aux;
        quantosNos++;
        aux->ant = ultimo;
        aux->prox = primeiro;
        primeiro->ant = aux;
        ultimo = aux;
        delete aux;
    }
}


template <class Dado>
void ListaCD<Dado>::insiraNoMeio(Dado novoDado)
{
    struct NoLista* aux  = new NoLista;
    aux->info = novoDado;
    struct NoLista* onde = primeiro;
    for(int i = 0; i<posAtual;i++)
    {
        onde = onde->prox;
    }
    onde->ant->prox = aux;
    aux->prox = onde;
    aux->ant = onde->ant;
    onde->ant = aux;


    if (onde == primeiro)
       primeiro = aux;

    quantosNos++;
}





template<class Dado>
void ListaCD<Dado>::insira(Dado novoDado)
{
    if(posAtual == 0)
    insiraNoComeco(novoDado);
    else
    insiraNoMeio(novoDado);
}

template<class Dado>
void ListaCD<Dado>::insiraDepois(Dado novoDado)
{
    if(posAtual == quantosNos - 1)
    insiraNoFim(novoDado);
    else
    {
        posAtual++;
        insiraNoMeio(novoDado);
        posAtual--;
    }

}

template<class Dado>
void ListaCD<Dado>::remova()
{
    struct NoLista* aux = primeiro;
    for(int i = 0; i <posAtual;i++)
        aux = aux->prox;
    if (!estaVazia())
      {
        if (aux == primeiro)
        {
            primeiro = primeiro->prox;
            if (estaVazia())
                ultimo = NULL;
            else
            {
                ultimo->prox = primeiro;
                primeiro->ant = ultimo;
            }
        }
        else
            if (aux == ultimo)
            {
                ultimo = aux->ant;
                ultimo->prox = primeiro;
                primeiro->ant = ultimo;
            }
            else
            {
                aux->ant->prox = aux->prox;
                aux->prox->ant = aux->ant;
            }

        quantosNos--;
      }
}

template<class Dado>
void ListaCD<Dado>::removaDepois()
{
    posAtual++;
    remova();
    posAtual--;
}


template<class Dado>
int ListaCD<Dado>::getPos()
{
    return posAtual;
}




template <class Dado>
Dado ListaCD<Dado>::infoAtual()
{
    struct NoLista *aux;
    aux = primeiro;
    for(int i = 0; i < this->posAtual;i++)
    {
        aux = aux->prox;
    }
    return aux->info;
}

template <class Dado>
void ListaCD<Dado>::avance()
{
    if(posAtual == quantosNos-1)
        posAtual = 0;
    else
    posAtual++;
}

template <class Dado>
void ListaCD<Dado>::retroceda()
{
    if(posAtual == 0)
        posAtual = quantosNos-1;
    else
    posAtual--;
}

template<class Dado>
void ListaCD<Dado>::printarLista()
{
    int pos = this->posAtual;
    for(posAtual = 0; posAtual <quantosNos;posAtual++)
    {
        std::cout << infoAtual();
        std::cout << std::endl;
    }

    posAtual = pos;

}

template<class Dado>
bool ListaCD<Dado>::estaVazia()
{
    return primeiro == NULL;
}


template<class Dado>
ListaCD<Dado> ListaCD<Dado>::operator=(const ListaCD& other)
{
    ListaCD lcd(other);
    return lcd;
}

template<class Dado>
ListaCD<Dado>::ListaCD(const ListaCD& other)
{
    this->posAtual   = other.posAtual;
    this->quantosNos = other.quantosNos;
    primeiro = new char;
    ultimo   = new char;
    for(int i = 0;i<other.posAtual;i++)
    {
        *(this->primeiro+i) = *(other.primeiro + i);
    }

}

#endif // LISTACD_H


