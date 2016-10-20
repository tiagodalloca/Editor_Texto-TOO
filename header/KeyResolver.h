#ifndef KEY_RESOLVER
#define KEY_RESOLVER

#include <stdlib>
#include <map>

using namespace std;

class KeyResolver{

public:
  KeyResolver();
  KeyResolver(const KeyResolver&);
  void start() const;
  void stop() const;
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

