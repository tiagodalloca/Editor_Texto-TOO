#include "String.h"
#include <stdlib.h>

char* conteudo;

String::String ()
{
    conteudo = (char*) malloc(sizeof(char) * 256);
}

String::String(char* novoCont)
{
    conteudo = novoCont;
}

String::String (unsigned int len)
{
    if(len <= 256)
        conteudo = (char*) malloc(len * sizeof(char) );
    else
        conteudo = (char*) malloc(sizeof(char) * 256);
}


String::~String ()
{
    free(conteudo);
}


int String::length() const
{
    for(int i = 0; i < 256;i++)
    {
        if(*(conteudo + i) == NULL)
            return i;
    }
}

void String::deleta(unsigned int posIni, unsigned int posFinal)
{
    for(int i = posIni; i<=posFinal; i++)
    {
        deletaCharAt(i);
    }
}

char& String::operator[](unsigned int pos) const
{
    return *(conteudo + pos);
}

void String::deletaCharAt(unsigned int pos)
{
    *(conteudo + pos) = ' ';
    int i;
    for(i = pos;i<length();i++)
    {
        *(conteudo + i) = *(conteudo + i + 1);
    }
    *(conteudo + i) = NULL;
}
void String::insere(unsigned int pos, char c)
{
    int i = length();
    for(i = length();i>pos;i--)
    {
        *(conteudo + i) = *(conteudo + i - 1);
    }
    *(conteudo + pos) = c;

    *(conteudo + length()-1)=NULL;
}

char* String::toString() const
{
    return conteudo;
}

void String::operator=(char *c)
{
    conteudo = c;
}
