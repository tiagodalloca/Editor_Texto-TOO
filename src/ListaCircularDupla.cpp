#include "ListaCircularDupla.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "String.h"

int posAtual;
int qtosNos;
struct NoLista
{
    String linha;
    NoLista *prox;
    NoLista *ant;

    NoLista()
    {
        linha = " ";
        prox = NULL;
        ant = NULL;
    }
};
NoLista *primeiro;
NoLista *ultimo;

ListaCircularDupla::ListaCircularDupla()
{
    primeiro =  ultimo = NULL;
    posAtual = 0;
}

ListaCircularDupla::~ListaCircularDupla()
{
    if(primeiro)
        delete[] primeiro;
    if(ultimo)
        delete[] ultimo;
}

void ListaCircularDupla::avance()
{

}

void ListaCircularDupla::insira(String novaLinha)
{
    NoLista* nozinho= new NoLista;
    nozinho->linha = novaLinha;
//    atual->ant = NULL;
//    atual->prox = NULL;
//
//    if(estaVazia())
//    {
//        primeiro ;
//        primeiro->linha = novaLinha;
//        ultimo = primeiro;
//    }
//    atual->prox = primeiro; // faz o novo nó apontar para o nó
//    atual->ant = ultimo;
//    primeiro->ant = atual;
//    ultimo->prox = atual;
//    primeiro = atual;      // atualmente no início da lista
//    qtosNos++;
//    posAtual = qtosNos - 1;

}

String ListaCircularDupla::infoAtual()
{

}
bool ListaCircularDupla::estaVazia()
{
    return primeiro == NULL ;
}
