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
}
void  Buffer::descerLinha()
{
    MyString* ms = new MyString();
    linhas->insiraNoFim(ms);
    linhas->avance();
    voltarAoInicioDaLinha();
}

void Buffer::voltarAoInicioDaLinha()
{
    coluna = 0;
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
    if(coluna >0)
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



void  Buffer::inserirLinha(MyString* linha)
{
    linhas->insiraNoFim(linha);
    linhas->avance();
}
void  Buffer::deletarADireita()
{
    if(coluna <= linhas->infoAtual()->length()){
      linhas->infoAtual()->deletaCharAt(coluna);
      coluna--;
    }
}
void  Buffer::deletarAEsquerda()
{
    if(coluna > 0)
        linhas->infoAtual()->deletaCharAt(--coluna);
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
