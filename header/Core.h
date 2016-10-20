#ifndef CORE
#define CORE

#include "String.h"
#include "Pilha.h"
#include "ListaCD.h"

class Core{
public:
  char* linhasAsString();
  void subirLinha();
  void descerLinha();
  void irParaEsquerda();
  void irParaDireita();
  void inserirCaracter(char);
  void inserirLinha();
  void deletarADireita();
  void deletarAEsquerda();
  char* getLinha(int);
private:
  ListaCD<String> linhas;
  unsigned int *coluna;
};
  
#endif
