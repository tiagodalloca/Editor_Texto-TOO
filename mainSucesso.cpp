#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "MyString.h"
#include "ListaCD.h"
#include "ListaSimples.h"
using namespace std;

int main()
{
char *c = (char*) malloc(sizeof(char) * 3);
c[0] = 'a';
c[1] = 'b';
c[2] = 'c';
c[3] = '\0';
MyString st(c);
cout << c;
cout << endl;
cout << st;
cout << endl;
ListaCD<MyString*>* l = new ListaCD<MyString*>;
MyString* s;
s = new MyString(st);
l->adicionarFinal(s);
ListaCD<char*>* lc = new ListaCD<char*>;
lc->adicionarFinal(st.toString());
cout << *(l->getPrimeiro());
cout << endl;
cout << lc->getPrimeiro();
cout << endl;
cout << l->getPrimeiro()->length();

return 0;
}
