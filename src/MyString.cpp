#include "MyString.h"
#include <stdlib.h>
#include <stdio.h>
#include <String.h>
using namespace std;
char* conteudo;
int tam ;

MyString::MyString ()
{
    tam = 256;
    conteudo = (char*) malloc(sizeof(char) * tam);
}

MyString::MyString(char* novoCont)
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

    conteudo[tam] = '\0';

}


void MyString::alteraCont(char* outro)
{
    conteudo = outro;
}

MyString::MyString (unsigned int len)
{
    if(len <= 256)
        conteudo = (char*) malloc(len * sizeof(char) );
    else
        conteudo = (char*) malloc(sizeof(char) * 256);
}


MyString::~MyString ()
{
    delete[] conteudo;
}


int MyString::length() const
{
    for(int i = 0; i < 256;i++)
    {
        if(*(conteudo + i) == NULL)
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

bool MyString::operator!=(MyString oso)
{
    MyString s(this->conteudo);
    if(oso == s)
        return false;
    return true;

}
bool MyString::operator>(MyString oso)
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

bool MyString::operator>=(MyString oso)
{
    MyString s(this->conteudo);
    if(s==oso)
    return true;

    return s>oso;
}

bool MyString::operator<(MyString oso)
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

bool MyString::operator<=(MyString oso)
{
    MyString s(this->conteudo);
    if(s == oso)
        return true;
    return s < oso;
}



bool MyString::operator==(MyString oso)
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
    *(conteudo + dpsDoFim) = c;
}
char& MyString::operator[](unsigned int pos) const
{
    return *(conteudo + pos);
}

void MyString::deletaCharAt(unsigned int pos)
{
    int i;
    for(i = pos;i<length();i++)
    {
        *(conteudo + i) = *(conteudo + i + 1);
    }
    *(conteudo + i) = NULL;
}
void MyString::insere(unsigned int pos, char c)
{
    int i = length();
    for(i = length();i>pos;i--)
    {
        *(conteudo + i) = *(conteudo + i - 1);
    }
    *(conteudo + pos) = c;

    *(conteudo + length()-1)=NULL;
}

char* MyString::toString() const
{
    return conteudo;
}

MyString& MyString::operator=(const MyString &oso)
{
//    return s;
}

MyString::MyString(const MyString &oso)
{

    this->conteudo =(char*)malloc(oso.length()*sizeof(char));
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
