#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include "KeyResolver.h"

using namespace std;

void f (){
  cout << "Ctrl-D \n";
}

void g(unsigned short int i){
  cout << (char) i << " " << i << "\n";
}

int main(int argsc, char** args){

  KeyResolver k = KeyResolver(&g);

  k.mapear(4, &f);
  k.mapear('p', []()->void{
      cout << "Vc pressionou pezinho! \n";
    });

  k.mapear('z', []()->void{
      cout << "Vc pressionou zezinho \n";
    });

  k[(unsigned short int) 'f'] = []()->void{
    cout << "Vc pressionou fzinho \n";
  };

  k['c'] = []()->void{
    cout << "Ola camila!";
  };

  k.mapear((unsigned int) 5, []()->void{
      cout << "Ctrl-E";
    }); //c-e
  
  while(true){
    // int i = getch();
    // cout << i << "\n";
    k.resolver();
  }
  
  return 0;
}
