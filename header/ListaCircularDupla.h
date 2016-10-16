#ifndef LISTACIRCULARDUPLA_H_INCLUDED
#define LISTACIRCULARDUPLA_H_INCLUDED
#include "String.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "String.h"

class ListaCircularDupla
{
    public:
        ListaCircularDupla();
        ~ListaCircularDupla();
        ListaCircularDupla(const ListaCircularDupla& other);
        ListaCircularDupla& operator=(const ListaCircularDupla& other);
        void insira(String novaLinha);
        void insiraDepois(String linha);
        void remova();
        void removaDepois();
        String infoAtual();
        void avance();
        void retroceda();
        bool estaVazia();



    protected:

    private:
        int posAtual ;
        struct NoLista
        {
            String linha;
            NoLista *prox;
            NoLista *ant;
        };
        NoLista *primeiro;
        NoLista *ultimo;
        int qtosNos;
};



#endif // LISTACIRCULARDUPLA_H_INCLUDED
