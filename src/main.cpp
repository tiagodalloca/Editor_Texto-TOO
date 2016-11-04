#include "Pilha.h"
#include "KeyResolver.h"
#include "Buffer.h"
#include "Misc.h"

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>

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
  buf_g.inserirCaracter(i);
  cout << (char) i;
}

char* _saveFileDialog(){
  char *filename = (char*) malloc(MAX_PATH*sizeof(char));
  // char filename[MAX_PATH];
  OPENFILENAME ofn;
  ZeroMemory( &ofn,      sizeof( ofn ) );
  ZeroMemory( filename,  sizeof( filename ) );
  ofn.lStructSize  = sizeof( ofn );
  ofn.hwndOwner    = NULL;  // If you have a window to center over, put its HANDLE here
  ofn.lpstrFilter  = "Text Files\0*.txt\0Any File\0*.*\0";
  ofn.lpstrFile    = filename;
  ofn.nMaxFile     = MAX_PATH;
  ofn.lpstrTitle   = "Select a File, yo!";
  ofn.Flags        = OFN_DONTADDTORECENT;

  if (GetSaveFileName( &ofn )){
    return filename;
  }

  return 0;
}

void _salvar(){
  char *filename;
  filename = _saveFileDialog();
  if (*filename){
    FILE *f;
    f = fopen(filename, "w");
    fprintf(f, "%s", buf_g.linhasAsString());
    fclose(f);
  }
}

int main(int argc, char **args){
  kr_g = KeyResolver(&_default);
  kr_g[19] = &_salvar;
  kr_g[8] = &_deletarCaracter;
  buf_g = Buffer();
  
  pilha_acoes = PilhaAcao();
  acoes_opostas_g = AcoesRelacionais();

  while(true){
    kr_g.resolver();
  }
}

