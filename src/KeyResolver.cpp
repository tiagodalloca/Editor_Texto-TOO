#include "KeyResolver.h"

static _default(unsigned short int i){
}

KeyResolver::KeyResolver(void (*f)(unsigned short int)) : defaultAction(f){
  associacoes = map<unsigned short int, void(*)()>();
}


KeyResolver::~KeyResolver(){
  associacoes = map<unsigned short int, void(*)()>();
}

KeyResolver::KeyResolver(const KeyResolver& oso){
}

KeyResolver::KeyResolver(){
  defaultAction = &_default;
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

void KeyResolver::mapear(const unsigned short int i, void (*f)()){
  associacoes[i] = f;
}

ponteiro_f KeyResolver::operator[](const unsigned short int& i){
  return associacoes[i];
}

ponteiro_f KeyResolver::operator[](unsigned short int& i){
  return associacoes[i];
}
