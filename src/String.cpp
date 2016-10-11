#include "String.h"
#include <stdlib.h>

char* conteudo;

String::String ()
{
    conteudo = (char*) malloc(sizeof(char) * 256);
}

String::String (unsigned int len)
{
    conteudo = (char*) malloc(sizeof(char) * len);
}

String::~String ()
{

}

char String::charAt(unsigned int pos) const
{
    return *(conteudo + pos);
}

int String::length() const
{

}

void String::deleta(unsigned int posIni, unsigned int posFinal)
{


}
void String::deletaCharAt(unsigned int pos)
{


}
void String::insere(unsigned int pos, char c)
{


}
void String::replacer(unsigned int pos, char c)
{


}
char* String::toString() const
{


}
