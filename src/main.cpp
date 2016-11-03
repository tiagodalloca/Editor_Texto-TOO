#include "Pilha.h"
#include "KeyResolver.h"
#include "Buffer.h"
#include "Misc.h"

#include <stdlib.h>
#include <iostream>
#include <stdio.h>

KeyResolver kr_g;
Buffer b_g;
PilhaAcao pilha_acoes;
AcoesRelacionais acoes_opostas_g;

int main(int argc, char **args){
  kr_g = KeyResolver(_defualt);
  b_g = Buffer();
  pilha_acoes = PilhaAcoes();
  acoes_opoes_g = AcoesRelacionais();
}
