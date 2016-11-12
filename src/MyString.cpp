#include "MyString.h"
#include <stdlib.h>
#include <stdio.h>
#include <String.h>
using namespace std;

MyString::MyString ()
{
    this->tam = 256;
    this->conteudo = (char*) malloc(sizeof(char) * this->tam);
    *conteudo = '\0';
}

MyString::MyString(char* novoCont)
{
   for(int i = 0; i < 256;i++)
    {
        if(*(novoCont + i) =='\0')
        {
           this->tam = i;
            break;
        }
    }

    this->conteudo = (char*) malloc((tam + 1) * sizeof(char));
    strcpy(this->conteudo ,novoCont);

}


void MyString::alteraCont(char* outro)
{
    this->conteudo = outro;
}

MyString::MyString (unsigned int len)
{
    if(len <= 256)
        this->conteudo = (char*) malloc(len * sizeof(char) );
    else
        this->conteudo = (char*) malloc(sizeof(char) * 256);
}


MyString::~MyString ()
{
    delete[] this->conteudo;
}


int MyString::length() const
{
    for(int i = 0; i < 256;i++)
    {
        if(*(this->conteudo + i) == '\0')
            return i;
    }
}

void MyString::deleta(unsigned int posIni, unsigned int posFinal)
{
    int diferenca = posFinal - posIni + 1;
    for(int i = 1; i<=diferenca; i++)
    {
        deletaCharAt(posIni);
    }
}


bool MyString::operator!=(const MyString& oso)
{
    MyString s(this->conteudo);
    if(s == oso)
        return false;
    return true;

}
bool MyString::operator>(const MyString& oso)
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

bool MyString::operator>=(const MyString& oso)
{
    MyString s(this->conteudo);
    if(s==oso)
    return true;

    return s>oso;
}

bool MyString::operator<(const MyString& oso)
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

bool MyString::operator<=(const MyString& oso)
{
    MyString s(this->conteudo);
    if(s == oso)
        return true;
    return s < oso;
}



bool MyString::operator==(const MyString& oso)
{
    if(oso.length()!=this->length())
        return false;

    for(int i = 0; i <this->length();i++)
    if(*(this->conteudo + i) != oso[i])
        return false;

    return true;


}
void MyString::append(char c)
{
    int dpsDoFim = length();
    *(this->conteudo + dpsDoFim) = c;
}


char& MyString::operator[](unsigned int pos) const
{
    return *(this->conteudo + pos);
}

void MyString::deletaCharAt(unsigned int pos)
{
    int i;
    for(i = pos;i<length();i++)
        *(this->conteudo + i) = *(this->conteudo + i + 1);

    *(this->conteudo + i) = NULL;
}
void MyString::insere(unsigned int pos, char c)
{
    for(int i = length() + 1;i>pos;i--)
    {
        *(this->conteudo + i) = *(this->conteudo + i - 1);
    }
    *(this->conteudo + pos) = c;
}

char* MyString::copiarChar(char* outro) const
{
    char* ret = (char*)malloc(strlen(outro)+1*sizeof(char));
    for(int i = 0; i < strlen(outro);i++)
    {
        *(ret + i) = *(outro + i);
    }
	*(ret + strlen(outro)) = '\0';

    return ret;

}

char* MyString::toString() const
{
    char* copia = copiarChar(conteudo);
    return copia;
}



MyString& MyString::operator=(const MyString &oso)
{
    MyString os(oso);
    return os;
}

MyString::MyString(const MyString &oso)
{

    this->conteudo =(char*)malloc(oso.length() + 1*sizeof(char));
    for(int i = 0; i < oso.length();i++)
    {
        *(this->conteudo + i) = (char)oso[i];
    }
    *(this->conteudo + oso.length()) = '\0';
}


ostream& operator<<(ostream& OS, const MyString& S)
{
return (OS << S.conteudo);
}

istream& operator>> (istream& IS, MyString& S)
{
IS >> S.conteudo;

return IS;
}
