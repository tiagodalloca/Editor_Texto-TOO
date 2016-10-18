#include <io.h>
#include <stdlib.h>
#include <stdio.h>
#include "conio.h"
#include "ListaSimples.h"
#include "Pilha.h"
#include "String.h"
using namespace std;

void printi(int i){
  printf("\n%i", i);
}

int main(){
  ListaSimples<int> *l = new ListaSimples<int>;
  Pilha<String> p = Pilha<String>();
  // Pilha<int> *p = new Pilha<int>;
  
  printf("Teste com a lista: \n");

  l->adicionarComeco(1);
  l->adicionarComeco(2);
  l->adicionarComeco(3);
  l->percorrer(&printi);
  
  l->adicionarFinal(1);
  l->adicionarFinal(2);
  l->adicionarFinal(3);
  l->retirarComeco();
  printf("\n");
  l->percorrer(&printi);

  l->retirarFinal();
  l->retirarFinal();
  printf("\n");
  l->percorrer(&printi);

  l->retirarComeco();
  l->retirarComeco();
  l->retirarComeco();

  printf("\n%i", l->getQuantos());
  
  printf("\n\nTeste com a pilha: \n");

  p.push(String("12345"));
  p.push(String("1234"));
  p.push(String("123"));
  p.push(String("12"));
  p.push(String("1"));
  
  while(!p.vazia()){
    printf("%i", p.getQuantos());
    printf("%s\n", p.pop().toString());
  }
  // p->push(1);
  // p->push(2);
  // p->push(3);
  // p->push(3);
  // p->push(4);

  // while(!p->vazia()){
  //   printf("%i ", p->getQuantos());
  //   printf("%i\n", p->pop());
  //   printf("-> %i \n", p->getQuantos());
  // }

  printf("Cabô");
  delete l;
  printf("Cabô");
  return 0;
}
