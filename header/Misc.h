#include "Pilha.h"
#include <stdlib.h>
#include <map>
#include <stdlib.h>

using namespace std;

typedef enum{
  esquerda, direita,
  inserirCaracter, backdel, frontdel,
  descer, subir,
  novaLinha
}Acao;

typedef struct{
  Acao acao;
  void **args;
}AcaoEncapsulada;

typedef map<const Acao, void(*)(void**)> AcoesRelacionais;
typedef Pilha<AcaoEncapsulada*> PilhaAcao;
