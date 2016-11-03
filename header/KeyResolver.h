#ifndef KEY_RESOLVER
#define KEY_RESOLVER

#include <stdlib.h>
#include <conio.h>
#include <map>

using namespace std;

class KeyResolver{

  typedef std::map<unsigned short int, void(*)()>::iterator iterator;
  typedef void(*ponteiro_f)();
  
public:
  KeyResolver();
  KeyResolver(void (*)(unsigned short int));
  ~KeyResolver();
  KeyResolver(const KeyResolver&);
  void resolver();
  void mapear(const unsigned short int, void(*)());
  ponteiro_f operator[](const unsigned short int&);
  ponteiro_f operator[](unsigned short int&);

private:
  map<unsigned short int, void(*)()>associacoes;
  void (*defaultAction)(unsigned short int);
};

#endif

/*
KeyResolver *kr = new KeyResolver;
kr->mapear("C-s", &salvar);
kr->start();
*/
