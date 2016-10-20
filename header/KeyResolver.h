#ifndef KEY_RESOLVER
#define KEY_RESOLVER

#include <stdlib>
#include <map>

using namespace std;

class KeyResolver{
  struct Binding{
    char* key;
    void(*f)();
  };
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
