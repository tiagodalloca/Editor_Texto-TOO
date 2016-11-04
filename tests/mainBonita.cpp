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
  b->inserirLinha(new MyString("Ctrl-D \n"));
  cout << "Ctrl-D \n";
  b->voltarAoInicioDaLinha();
}

void g(unsigned short int i){
  b->inserirLinha(new MyString((char) i));
  cout << (char) i << " " << i << "\n";
  b->voltarAoInicioDaLinha();

}

void sbLinha()
{
    b->subirLinha();
    int x = b->getPosX();
    int y = b->getPosY();
    gotoXY(x,y);
}

void ldDireito()
{
    b->irParaDireita();
    int x = b->getPosX();
    int y = b->getPosY();
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
  k.mapear('\t',&sbLinha);
  k.mapear(12,&ldDireito);
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
