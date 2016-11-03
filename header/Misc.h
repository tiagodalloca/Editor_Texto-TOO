#include "Pilha.h"
#include <stdlib.h>
#include <map>

using namespace std;

typedef enum{
  esquerda, direita,
  inserirCaracter,
  descer, subir,
  novaLinha
}Acao;

typedef map<Acao, void(*)()> AcoesRelacionais;
typedef Pilha<Acao> PilhaAcao;
