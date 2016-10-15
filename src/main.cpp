#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "ListaSimples.h"
using namespace std;

void printi(int i){
  printf("\n%i", i);
}

int main(){
  ListaSimples<int> *l = new ListaSimples<int>();
  l->adicionarComeco(1);
  l->adicionarComeco(2);
  l->adicionarComeco(3);
  l->percorrer(&printi);

  l->retirarComeco();
  l->retirarComeco();
  l->retirarComeco();
  
  l->adicionarFinal(1);
  l->adicionarFinal(2);
  l->adicionarFinal(3);
  l->percorrer(&printi);
  
  return 0;
}

