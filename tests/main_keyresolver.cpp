#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include "KeyResolver.h"

using namespace std;

void f (){
  cout << "Ctrl-D \n";
}

void g(unsigned int i){
  cout << (char) i << " " << i << "\n";
}

int main(int argsc, char** args){

  KeyResolver k = KeyResolver(&g);

  k.mapear((unsigned int) 4, &f);
  k.mapear('p', []()->void{
      cout << "Vc pressionou pezinho!";
    });

  k.mapear('z', []()->void{
      cout << "Vc pressionou zezinho";
    });
  
  
  while(true){
    // int i = getch();
    // cout << i << "\n";
    k.resolver();
  }
  
  return 0;
}
