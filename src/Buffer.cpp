#include "Buffer.h"
#include <stdlib.h>
#include "MyString.h"
#include <string.h>


Buffer::Buffer()
{
  coluna = 0;
  linhas  = new ListaCD<MyString*>;
  MyString* ms = new MyString();
  linhas->insiraNoFim(ms);
}

Buffer::Buffer(ListaCD<MyString*>* novaLista)
{
  linhas  = novaLista;
}


char* Buffer::linhasAsString()
{
  char* laStr = (char*)malloc(tam*(256+1)*sizeof(char));
  *(laStr) = '\0';

  while(linhas->naoChegouAoFim()){
    char* temp = linhas->infoAtual()->toString();
    strcat(laStr, temp);
    strcat(laStr, "\r\n");
  }
  return laStr;
}
void  Buffer::subirLinha()
{
  linhas->retroceda();
  unsigned int novaColuna = linhas->infoAtual()->length();
  if (coluna > novaColuna)
    coluna = novaColuna;
}
void  Buffer::descerLinha()
{
  linhas->avance();
  unsigned int novaColuna = linhas->infoAtual()->length();
  if (coluna > novaColuna)
    coluna = novaColuna;
}

void Buffer::inserirLinha(){
  MyString* ms = new MyString();
  linhas->insiraNoFim(ms);
  linhas->avance();
  voltarAoInicioDaLinha();
}

void Buffer::voltarAoInicioDaLinha()
{
  coluna = 0;
}

void Buffer::irAoFimDaLinha()
{
    coluna = linhas->infoAtual()->length();
}

int Buffer::tamanhoLinha()
{
    return linhas->infoAtual()->length();
}

void Buffer:: subirPagina()
{
    int i = 0;
    for(;i<5;i++)
    {
        if(linhas->getPos() == 0)
        {
            unsigned int novaColuna = linhas->infoAtual()->length();
            if (coluna > novaColuna)
                coluna = novaColuna;
            break;
        }
        linhas->retroceda();
    }
    if(i == 5)
    {
        unsigned int novaColuna = linhas->infoAtual()->length();
        if (coluna > novaColuna)
            coluna = novaColuna;
    }
}

void Buffer:: descerPagina()
{
    int i = 0;
    for(; i<5;i++)
    {
        if(linhas->getPos() == linhas->quantos() - 1)
        {
            unsigned int novaColuna = linhas->infoAtual()->length();
            if (coluna > novaColuna)
                coluna = novaColuna;
            break;
        }

        linhas->avance();
    }
    if(i == 5)
    {
        unsigned int novaColuna = linhas->infoAtual()->length();
        if (coluna > novaColuna)
            coluna = novaColuna;
    }
}

int Buffer::getPosY()
{
  return linhas->getPos();
}

int Buffer::getPosX()
{
  return coluna;
}

void  Buffer::irParaEsquerda()
{
  if(coluna > 0)
    coluna--;
}
void  Buffer::irParaDireita()
{
  if(coluna<255 && coluna < linhas->infoAtual()->length())
    coluna++;
}
bool  Buffer::inserirCaracter(char c)
{
  if(coluna < 255)
    {
      linhas->infoAtual()->insere(coluna,c);
      coluna++;
      return true;
    }
  return false;

}

void Buffer::setX(int i)
{
    if(i >=0 && i<linhas->infoAtual()->length())
        coluna = i;
}
void Buffer::setY(int i)
{
    while(linhas->naoChegouAoFim())
    {
        linhas->avance();
    }
}

int Buffer::quantasLinhas()
{
    return linhas->quantos();
}

void Buffer::inserirLinha(MyString* linha)
{
  linhas->insiraNoFim(linha);
  linhas->avance();
}
char Buffer::deletarADireita()
{
  if(coluna <= linhas->infoAtual()->length()){
    char ret = (*(linhas->infoAtual()))[coluna - 1];
    linhas->infoAtual()->deletaCharAt(coluna);
    coluna--;
    return ret;
  }

  return 0;
}
char Buffer::deletarAEsquerda()
{
  if(coluna > 0){
    char ret = (*(linhas->infoAtual()))[coluna - 1];
    //char ret = linhas->infoAtual()->operator[](coluna);
    linhas->infoAtual()->deletaCharAt(--coluna);
    return ret;
  }

  return 0;
}
char* Buffer::getLinha(unsigned int i)
{
  char *c = (char*)malloc(255*sizeof(char));
  try
    {
      c = linhas->getInfo(i)->toString();
      *(c + linhas->getInfo(i)->length())='\0';
    }
  catch( const std::invalid_argument& e ) {
    throw e;
  }
  return c;
}
