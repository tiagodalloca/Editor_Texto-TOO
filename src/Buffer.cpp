#include "Buffer.h"
#include <stdlib.h>

Buffer::Buffer()
{
    linhas  = new ListaCD<MyString*>;
    coluna = (unsigned int*)malloc(256*sizeof(int));
}

Buffer::Buffer(ListaCD<MyString*>* novaLista)
{
    linhas  = novaLista;
    coluna = (unsigned int*)malloc(256*sizeof(int));
}


char* Buffer::linhasAsString()
{
    char* laStr;

}
void  Buffer::subirLinha()
{

}
void  Buffer::descerLinha()
{

}
void  Buffer::irParaEsquerda()
{

}
void  Buffer::irParaDireita()
{

}
void  Buffer::inserirCaracter(char)
{

}
void  Buffer::inserirLinha()
{

}
void  Buffer::deletarADireita()
{

}
void  Buffer::deletarAEsquerda()
{

}
char* Buffer::getLinha(unsigned int)
{

}
