#ifndef KEY_RESOLVER
#define KEY_RESOLVER

#include <stdlib.h>
#include <conio.h>
#include <map>

using namespace std;

class KeyResolver{

  typedef std::map<unsigned int, void(*)()>::iterator iterator;
  
public:
  KeyResolver(void (*)(unsigned int));
  ~KeyResolver();
  KeyResolver(const KeyResolver&);
  void resolver();
  void mapear(const unsigned int, void(*)());
  void mapear(const char, void(*)());

private:
  map<unsigned int, void(*)()>associacoes;
  void (*defaultAction)(unsigned int);
};

#endif

/*
KeyResolver *kr = new KeyResolver;
kr->mapear("C-s", &salvar);
kr->start();
*/
