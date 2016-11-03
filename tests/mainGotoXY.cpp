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
  b->voltarAoInicio();
}

void z()
{
    cout<< "tecla para cima \n";
    b->subirLinha();
    int x = b->getPosX();
    cout << endl;
    cout << x;
    cout << endl;
    int y = b->getPosY();
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
    b->descerLinha();
    cout << endl;
}

void p(){
}
int main()
{
//    cout << "primeira linha" << endl;
//    cout << "segunda linha" << endl;
//    gotoXY(0,0);
//    char* linha = (char*)malloc(4*sizeof(char));
//    scanf("%s",linha);


KeyResolver k = KeyResolver(&g);

  k.mapear(72,&y);
  k.mapear('\n',&cj);
  k.mapear('\t',&z);
  k.mapear(4, &f);
  k.mapear(13,&pl);

  k.mapear('p', []()->void{
      b->inserirCaracter('p');
      cout << 'p' ;
    });

  k.mapear('a',[]()->void{
      b->inserirCaracter('a');
      cout << 'a';
    });

  k.mapear('z', []()->void{
      cout << "Vc pressionou zezinho \n";
    });

  k.mapear((unsigned int) 5, []()->void{
      cout << "Ctrl-E";
    }); //c-e

  while(true){
//     int i = getch();
//     cout << i << "\n";
    k.resolver();
  }


return 0;
}
