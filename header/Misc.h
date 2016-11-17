#include "Pilha.h"
#include <stdlib.h>
#include <map>

using namespace std;

typedef enum{
  esquerda, direita,
  inserirCaracter, backdel, frontdel,
  descer, subir,
  excluirLinhaEmbaixo, excluirLinha, novaLinha,
  endHome, upDown
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
