#ifndef BUFFER
#define BUFFER

#include "MyString.h"
#include "ListaCD.h"

class Buffer{
public:
  Buffer();
  Buffer(int tam);
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
  char charADireita();
  char deletarAEsquerda();
  char* getLinha(unsigned int);
  int getPosY();
  void voltarAoInicioDaLinha();
  int getPosX();
  void irAoFimDaLinha();
  void descerPagina();
  void subirPagina();
  void inserirLinhaDepois();
  void inserirLinhaDepois(MyString* ms);
  int tamanhoMax();
  int tamanhoLinha();
  int quantasLinhas();
  void setX(unsigned int i);
  void setY(unsigned int i);
	char* getRestoLinha();
  
private:
  ListaCD<MyString*>* linhas;
  unsigned int coluna;
  int tam = 0;
  int tamMax = 0;
};

#endif
