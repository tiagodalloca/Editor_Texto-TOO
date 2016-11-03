#include "Pilha.h"
#include "KeyResolver.h"
#include "Buffer.h"
#include "Misc.h"

#include <stdlib.h>
#include <iostream>
#include <stdio.h>

KeyResolver kr_g;
Buffer buf_g;
PilhaAcao pilha_acoes;
AcoesRelacionais acoes_opostas_g;

void _direita(){
  buf_g.irParaDireita();
  pilha_acoes.push(direita);
}

void _desfazer(){
  Acao a = pilha_acoes.pop();
  acoes_opostas_g[a]();
}

void _esquerda(){
  buf_g.irParaEsquerda();
}

void _descer(){
  buf_g.descerLinha();
}

void _subir(){
  buf_g.subirLinha();
}

void _deletarCaracter(){
  buf_g.deletarADireita();
}

void _default(unsigned short int i){
  buf_g.inserirCaracter((char) i);
}

int main(int argc, char **args){
  kr_g = KeyResolver(&_default);
  buf_g = Buffer();
  pilha_acoes = PilhaAcao();
  acoes_opostas_g = AcoesRelacionais();
}

