#ifndef MyString_H_INCLUDED
#define MyString_H_INCLUDED
#include <iostream>
using namespace std;

class MyString
{
    private:
        char* conteudo;
        int tam;

    public:
        MyString();
        MyString(unsigned int len);
        MyString(char* contNovo);
        ~MyString();
        int length() const;
        void deleta(unsigned int posIni, unsigned int posFinal);
        void deletaCharAt(unsigned int pos);
        void insere(unsigned int pos, char c);
        char& operator[](unsigned int pos) const;
        char* toString() const;
        void alteraCont(char* outro);
        void append(char c);
        bool operator >(const MyString& oso);
        bool operator >=(const MyString& oso);
        bool operator ==(const MyString& oso);
        bool operator <(const MyString& oso) ;
        bool operator <=(const MyString& oso) ;
        bool operator !=(const MyString& oso) ;
        MyString& operator=(const MyString& oso);
        MyString(const MyString& oso);
        friend ostream& operator<< (ostream&, const MyString&);
        friend istream& operator>> (istream&, MyString&);
};


#endif // MyString_H_INCLUDED
