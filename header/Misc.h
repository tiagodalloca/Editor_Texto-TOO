#include "Pilha.h"
#include <stdlib.h>
#include <map>

using namespace std;

typedef enum{
  esquerda, direita,
  inserirCaracter, backdel, frontdel,
  descer, subir,
  excluirLinhaEmbaixo, excluirLinha, novaLinha,
  endi,homi,meioEndi,meioHomi, up, down, meioDown, meioUp
}Acao;

typedef struct{
  Acao acao;
  void **args;
}AcaoEncapsulada;

typedef enum{
  desfazer, refazer
}DesfazerRefazer;

typedef map<const Acao,
            void(*)(void**, DesfazerRefazer)>
AcoesRelacionais;
typedef Pilha<AcaoEncapsulada*> PilhaAcao;
