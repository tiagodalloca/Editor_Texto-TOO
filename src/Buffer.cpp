#include "Buffer.h"
#include <stdlib.h>
#include "MyString.h"
#include <string.h>

Buffer::Buffer()
{
    linhas  = new ListaCD<MyString*>;
}

Buffer::Buffer(ListaCD<MyString*>* novaLista)
{
    linhas  = novaLista;
}


std::string Buffer::linhasAsString()
{
    char* laStr = (char*)malloc(2*sizeof(char));
    char c;
    while(linhas->naoChegouAoFim())
    {
        int len = linhas->infoAtual()->length();
        *(laStr + tam) = '\0';
        tam+=len;
        for(int i = 0; i < len;i++)
        {
            MyString s(laStr);
            int dpsDoFim = s.length();
            c = *(linhas->infoAtual()->toString() + i);
            *(laStr + dpsDoFim) = c;
            *(laStr + dpsDoFim + 1) = '\0';
        }
        MyString s2(laStr);
        *(laStr + tam) = '\n';
        *(laStr + tam+1) = '\0';
        tam++;
    }
    tam--;
    *(laStr + tam) = '\0';

    return laStr;
}
void  Buffer::subirLinha()
{
    linhas->avance();
}
void  Buffer::descerLinha()
{
    linhas->retroceda();
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
void  Buffer::inserirCaracter(char c)
{
    linhas->infoAtual()->insere(coluna,c);
}
void  Buffer::inserirLinha(MyString* linha)
{
    linhas->insiraNoFim(linha);
}
void  Buffer::deletarADireita()
{
    if(coluna < linhas->infoAtual()->length())
    linhas->infoAtual()->deletaCharAt(coluna);
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
