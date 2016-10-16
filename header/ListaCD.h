#ifndef LISTACD_H
#define LISTACD_H

template<class Dado>
struct NoLista{
  Dado info;
  struct NoLista<Dado> *prox;
};
template<class Dado>
class ListaCD
{
    public:
        ListaCD();
        ~ListaCD();
        ListaCD(const ListaCD& other);
        ListaCD& operator=(const ListaCD& other);
        void insira(Dado novo);
        void insiraDepois(Dado novo);
        void remova();
        void removaDepois();
        Dado infoAtual();
        void avance();
        void retroceda();
        bool estaVazia();

    protected:

    private:
        int posAtual ;
        NoLista<Dado> *primeiro;
        NoLista<Dado> *ultimo;
};

template <class Dado>
ListaCD<Dado>::ListaCD()
{
    posAtual = 0;
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
void ListaCD<Dado>::insira(Dado inf)
{
    primeiro = new NoLista<Dado>;
    primeiro->info = inf;
}

template <class Dado>
Dado ListaCD<Dado>::infoAtual()
{
    return primeiro->info;
}
#endif // LISTACD_H


