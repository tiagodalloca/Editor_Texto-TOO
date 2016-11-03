#ifndef KEY_RESOLVER
#define KEY_RESOLVER

#include <stdlib.h>
#include <conio.h>
#include <map>

using namespace std;

template<class C>
class KeyResolver{

  typedef typename std::map<unsigned short int, void(C::*)()>::iterator iterator;
  typedef void(C::*ponteiro_f)();
  
public:
  KeyResolver();
  KeyResolver(void (C::*)(unsigned short int));
  // ~KeyResolver();
  KeyResolver(const KeyResolver&);
  void resolver();
  void mapear(const unsigned short int, void(C::*)());
  ponteiro_f operator[](const unsigned short int&);
  ponteiro_f operator[](unsigned short int&);

private:
  map<unsigned short int, void(C::*)()> associacoes;
  void (C::*defaultAction)(unsigned short int);
};

template<class C>
KeyResolver<C>::KeyResolver(void (C::*f)(unsigned short int)) : defaultAction(f){
  associacoes = map<unsigned short int, void(C::*)()>();
}

// template<class C>
// KeyResolver<C>::~KeyResolver(){
//   associacoes = map<unsigned short int, void(C::*)()>();
// }

template<class C>
KeyResolver<C>::KeyResolver(const KeyResolver<C>& oso){
}

template<class C>
void KeyResolver<C>::resolver(){
  iterator it;
  int i = getch();
  it = associacoes.find(i);
  if (it != associacoes.end()){
    it->second();
  }
  else
    defaultAction(i);
}

template<class C>
void KeyResolver<C>::mapear(const unsigned short int i, void (C::*f)()){
  associacoes[i] = f;
}

template<class C>
typename KeyResolver<C>::ponteiro_f KeyResolver<C>::operator[](const unsigned short int& i){
  return associacoes[i];
}

template<class C>
typename KeyResolver<C>::ponteiro_f KeyResolver<C>::operator[](unsigned short int& i){
  return associacoes[i];
}


#endif

/*
KeyResolver *kr = new KeyResolver;
kr->mapear("C-s", &salvar);
kr->start();
*/
