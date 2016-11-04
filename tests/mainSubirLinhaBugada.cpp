#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "MyString.h"
#include "ListaCD.h"
#include "ListaSimples.h"
#include "Buffer.h"
#include "KeyResolver.h"
#include <windows.h>

using namespace std;

Buffer* b = new Buffer();

void gotoXY(int x, int y)
{
    static HANDLE h = NULL;
    if(!h)
        h=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x , y}; SetConsoleCursorPosition(h,c);
}



void f (){
  cout << "Ctrl-D \n";
}

void g(unsigned short int i){
  cout << (char) i << " " << i << "\n";
  MyString em((char)i);
  MyString* ms = new MyString(em);
  b->inserirLinha(ms);
  b->voltarAoInicioDaLinha();
}

void z()
{
    int y = b->getPosY();
    cout << endl;
    cout << y;
    cout << endl;
    b->subirLinha();
    int x = b->getPosX();
    cout << endl;
    cout << x;
    cout << endl;
    y = b->getPosY();
    cout << endl;
    cout << y;
    cout << endl;
    gotoXY(x,y);
}

void y()
{

}

void cj()
{
    b->irParaEsquerda();
    int x = b->getPosX() - 1;
    int y = b->getPosY();
    gotoXY(x,y);
}

void pl()
{
    cout << endl;
}

void p(){
}
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
