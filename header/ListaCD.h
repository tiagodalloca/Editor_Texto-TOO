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
        ListaCD operator=(const ListaCD& other);
        void insiraNoComeco(Dado novo);
        void insiraNoMeio(Dado novo);
        void insiraNoFim(Dado novo);
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

template<class Dado>
void ListaCD<Dado>::insiraNoComeco(Dado novoDado)
{
    struct NoLista<Dado>* aux = new NoLista<Dado>;
    aux->info = novoDado;
    if (estaVazia())       // se a lista está vazia, estamos
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

template <class Dado>
void ListaCD<Dado>::insiraNoFim(Dado novoDado)
{
    struct NoLista<Dado>* aux = new NoLista<Dado>;
    aux->info = novoDado;
    if (estaVazia())
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
    delete aux;
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
    struct NoLista<Dado>* aux = primeiro;
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
    {
        std::cout << infoAtual();
        std::cout<<std::endl;
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
    ListaCD<Dado> lcd(other);
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


