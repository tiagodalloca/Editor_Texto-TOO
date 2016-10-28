#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "MyString.h"
#include "ListaCD.h"
#include "ListaSimples.h"
#include "Buffer.h"

using namespace std;

int main()
{
char *c = (char*) malloc(sizeof(char) * 4);
c[0] = 'a';
c[1] = 'b';
c[2] = 'c';
c[3] = '\0';
MyString st(c);
char*d = (char*)malloc(sizeof(char)*5);
d[0] = 'c';
d[1] = 'a';
d[2] = 'f';
d[3] = 'e';
d[4] = '\0';
MyString st2(d);
cout << c;
cout << endl;
cout << st;
cout << endl;
ListaCD<MyString*>* l = new ListaCD<MyString*>;
MyString* s;
MyString* s2;
s2 = new MyString(st2);
s = new MyString(st);
l->insiraNoFim(s);
cout << *(l->infoAtual())<<endl;
cout << l->getPrimeiro()->length();
cout << endl;
Buffer* b = new Buffer(l);
cout << l->quantos() << endl;
b->inserirLinha(s2);
cout << b->linhasAsString();
cout << endl;
cout << endl;
cout << b->getLinha(1);
cout << endl;
cout << endl;
return 0;
}
