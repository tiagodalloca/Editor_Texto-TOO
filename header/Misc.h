#include "Pilha.h"
#include <stdlib.h>

typedef enum{
  esquerda, direita,
  inserirCaracter,
  descer, subir,
  novaLinha
}Acao;

typedef std::map<Acoes, void(*)()> AcoesRelacionais;
typedef Pilha<Acao> PilhaAcao;
