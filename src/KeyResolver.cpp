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
  
}

void KeyResolver::mapear(const char *c, void (*f)()){

}
