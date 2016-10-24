#include "KeyResolver.h"

map<char*, void()> associacoes;

KeyResolver::KeyResolver(){
  associacoes = map<char*, void()>();
}

KeyResolver::KeyResolver(const KeyResolver& oso){
  
}


KeyResolver::~KeyResolver(){
  delete associacoes;
}

void KeyResolver::resolver(){
  iterator it;
  int i = getch();
  it = associacoes.find(i);
  if (it != associacoes.end()){
    it->second();
    ungetch(i);
  }
}

void KeyResolver::mapear(const unsigned int i, void (*f)()){
  associacoes[i] = f;
}
