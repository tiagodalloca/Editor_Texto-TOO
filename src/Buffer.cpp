#include "Buffer.h"
#include <stdlib.h>
#include "MyString.h"

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
    char* laStr = (char*)malloc(2*sizeof(char));
    char c;
    while(linhas->naoChegouAoFim())
    {
        int len = linhas->infoAtual()->length();
        laStr = (char*)malloc((tam+1)*sizeof(char));
        *(laStr ) = '\0';
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
        *(laStr + s2.length()) = '\n';
        *(laStr + s2.length()+1) = '\0';
    }

    return laStr;
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
void  Buffer::inserirLinha(MyString* linha)
{
    linhas->insiraNoFim(linha);
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
