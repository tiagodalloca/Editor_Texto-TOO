#include "KeyResolver.h"

map<unsigned int, void(*)()> associacoes;
void (*defaultAction)(unsigned int);

KeyResolver::KeyResolver(void (*f)(unsigned int)) : defaultAction(f){
  associacoes = map<unsigned int, void(*)()>();
}

KeyResolver::KeyResolver(const KeyResolver& oso){
  associacoes = map<unsigned int, void(*)()>(oso.associacoes);
}


KeyResolver::~KeyResolver(){

}

void KeyResolver::resolver(){
  iterator it;
  int i = getch();
  it = associacoes.find(i);
  if (it != associacoes.end()){
    it->second();
  }
  else
    defaultAction(i);
}

void KeyResolver::mapear(const unsigned int i, void (*f)()){
  associacoes[i] = f;
}

void KeyResolver::mapear(const char c, void (*f)()){
  mapear((unsigned int) c, f);
}
