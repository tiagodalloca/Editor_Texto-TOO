#ifndef LISTACD_H
#define LISTACD_H
#include "String.h"

template <class Dado>
struct NoLista{
  Dado info;
  struct NoLista<Dado> *prox;
  struct NoLista<Dado> *ant;
};
template<class Dado>
class ListaCD
{
    public:
        ListaCD();
        ~ListaCD();
        ListaCD(const ListaCD& other);
        ListaCD& operator=(const ListaCD& other);
        void insiraAntes(Dado novo);
        void insira(Dado novo);
        void insiraNoFim(Dado novo);
        void insiraNoMeio(Dado novo);
        void remova();
        void removaDepois();
        Dado infoAtual();
        void avance();
        void retroceda();
        int getPos();
        bool estaVazia();
        void printarLista();

    protected:

    private:
        int posAtual = 0;
        int quantosNos = 0;
        NoLista<Dado> *primeiro;
        NoLista<Dado> *ultimo;
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


template <class Dado>
void ListaCD<Dado>::insiraNoFim(Dado novoDado)
{
    struct NoLista<Dado>* aux = new NoLista<Dado>;
    aux->info = novoDado;
    if (primeiro == NULL)
    {
        primeiro = ultimo = aux;
    }
    else
    ultimo->prox = aux;

    quantosNos++;
    aux->ant = ultimo;
    aux->prox = primeiro;
    primeiro->ant = aux;
    ultimo = aux;
}

template <class Dado>
void ListaCD<Dado>::insiraNoMeio(Dado novoDado)
{
    struct NoLista<Dado>* aux  = new NoLista<Dado>;
    aux->info = novoDado;
    struct NoLista<Dado>* onde = primeiro;
    for(int i = 0; i<posAtual;i++)
    {
        onde = onde->prox;
    }
    onde->ant->prox = aux;   // liga anterior ao novo
    aux->prox = onde;      // e novo no atual
    aux->ant = onde->ant;
    onde->ant = aux;


    if (onde == primeiro)  // se incluiu antes do início da lista,
       primeiro = aux;     // atualiza o apontador primeiro

    quantosNos++;           // incrementa número de nós da lista
}




template<class Dado>
void ListaCD<Dado>::insira(Dado novoDado)
{
    if(posAtual == 0)
    insiraAntes(novoDado);
    else
    insiraNoMeio(novoDado);

}


template<class Dado>
void ListaCD<Dado>::removaDepois()
{
    struct NoLista<Dado>* aux = primeiro;
    for(int i = 0; i < quantosNos; i++)

    ultimo = atual->ant;
    ultimo.Prox = primeiro;
    primeiro.Anterior = ultimo;
}


template<class Dado>
int ListaCD<Dado>::getPos()
{
    return posAtual;
}


template<class Dado>
void ListaCD<Dado>::insiraAntes(Dado novoDado)
{
    struct NoLista<Dado>* aux = new NoLista<Dado>;
    aux->info = novoDado;
    if (primeiro == NULL)       // se a lista está vazia, estamos
    {
    ultimo = primeiro = aux; // incluindo o 1o e o último nós!
    }

    aux->prox = primeiro; // faz o novo nó apontar para o nó
    aux->ant = ultimo;
    primeiro->ant = aux;
    ultimo->prox = aux;
    primeiro = aux;      // atualmente no início da lista
    quantosNos++;           // (que pode ser null)

}

template <class Dado>
Dado ListaCD<Dado>::infoAtual()
{
    struct NoLista<Dado> *aux;
    aux = primeiro;
    for(int i = 0; i <posAtual;i++)
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
    int pos = posAtual;
    for(posAtual = 0; posAtual <quantosNos;posAtual++)
        std::cout << infoAtual();
    posAtual = pos;
    std::cout<<std::endl;
}
#endif // LISTACD_H


