#ifndef BUFFER
#define BUFFER

#include "String.h"
#include "Pilha.h"
#include "ListaCD.h"

class Buffer{
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
  char* getLinha(unsigned int);
private:
  ListaCD<String> linhas;
  unsigned int *coluna;
};
  
#endif
