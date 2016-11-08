#ifndef BUFFER
#define BUFFER

#include "MyString.h"
#include "ListaCD.h"

class Buffer{
public:
  Buffer();
  Buffer(ListaCD<MyString*>* novaLista);
  char* linhasAsString();
  void subirLinha();
  void descerLinha();
  void irParaEsquerda();
  void irParaDireita();
  bool inserirCaracter(char);
  void inserirLinha(MyString* linha);
  void inserirLinha();
  char deletarADireita();
  char deletarAEsquerda();
  char* getLinha(unsigned int);
  int getPosY();
  void voltarAoInicioDaLinha();
  int getPosX();
  void irAoFimDaLinha();
  void descerPagina();
  void subirPagina();
  int tamanhoLinha();
  void setX(int i);
  void setY(int i);
  int quantasLinhas();

private:
  ListaCD<MyString*>* linhas;
  unsigned int coluna;
  int tam = 0;
};

#endif
