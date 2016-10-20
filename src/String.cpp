#include "String.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;
char* conteudo;
int tam ;

String::String ()
{
    tam = 256;
    conteudo = (char*) malloc(sizeof(char) * tam);
}

String::String(char* novoCont)
{
   for(int i = 0; i < 256;i++)
    {
        if(*(novoCont + i) =='\0')
        {
            tam = i;
            break;
        }

    }

    conteudo = (char*) malloc((tam + 1) * sizeof(char));

    strncpy(conteudo ,novoCont, tam + 1);

}


void String::alteraCont(char* outro)
{
    conteudo = outro;
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
    delete[] conteudo;
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
    int diferenca = posFinal - posIni + 1;
    for(int i = 1; i<=diferenca; i++)
    {
        deletaCharAt(posIni);
    }
}

bool String::operator!=(String oso)
{
    String s(this->conteudo);
    if(oso == s)
        return false;
    return true;

}
bool String::operator>(String oso)
{
    int menor;
    if(this->length() < oso.length())
        menor = this->length();
    else
        menor = oso.length();
    for(int i = 0; i <menor;i++)
    {
        if(*(this->conteudo + i)!= oso[i])
        {
            if((*(this->conteudo + i) > oso[i]))
            {
                return true;
            }
            return false;
        }
    }
    return this->length() > oso.length();
}

bool String::operator>=(String oso)
{
    String s(this->conteudo);
    if(s==oso)
    return true;

    return s>oso;
}

bool String::operator<(String oso)
{
    int menor;
    if(this->length() < oso.length())
        menor = this->length();
    else
        menor = oso.length();
    for(int i = 0; i <menor;i++)
    {
        if(*(this->conteudo + i)!= oso[i])
        {
            if((*(this->conteudo + i) < oso[i]))
            {
                return true;
            }
            return false;
        }
    }
    return this->length() < oso.length();
}

bool String::operator<=(String oso)
{
    String s(this->conteudo);
    if(s == oso)
        return true;
    return s < oso;
}



bool String::operator==(String oso)
{
    if(oso.length()!=this->length())
        return false;

    for(int i = 0; i <this->length();i++)
    if(*(this->conteudo + i) != oso[i])
        return false;

    return true;


}
void String::append(char c)
{
    int dpsDoFim = length();
    *(conteudo + dpsDoFim) = c;
}
char& String::operator[](unsigned int pos) const
{
    return *(conteudo + pos);
}

void String::deletaCharAt(unsigned int pos)
{
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

String& String::operator=(const String &oso)
{
//    return s;
}

String::String(const String &oso)
{

    this->conteudo =(char*)malloc(oso.length()*sizeof(char));
    for(int i = 0; i < oso.length();i++)
    {
        *(this->conteudo + i) = (char)oso[i];
    }
}


ostream& operator<<(ostream& OS, const String& S)
{
return (OS << S.conteudo);
}

istream& operator>> (istream& IS, String& S)
{
IS >> S.conteudo;

return IS;
}
