#ifndef EDITOR
#define EDITOR

#include "String.h"
#include "Pilha.h"
#include "ListaCD.h"

class Editor{
public:
  char *linhasAsString();
  void subirLinha();
  void descerLinha();
  void irParaEsquerda();
  void irParaDireita();
private:
  ListaCD<String> linhas;
  unsigned int *coluna;
};
  
#endif
