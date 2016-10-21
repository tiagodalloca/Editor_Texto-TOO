#ifndef KEY_RESOLVER
#define KEY_RESOLVER

#include <stdlib.h>
#include <conio.h>
#include <map>

using namespace std;

class KeyResolver{

public:
  KeyResolver();
  KeyResolver(const KeyResolver&);
  void resolver();
  void mapear(const char*, void());

private:
  map<char*, void()> associacoes;
};

#endif

/*
KeyResolver *kr = new KeyResolver;
kr->mapear("C-s", &salvar);
kr->start();
*/
