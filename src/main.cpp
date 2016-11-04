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
char quit;

void gotoXY(int x, int y)
{
    static HANDLE h = NULL;
    if(!h)
        h=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x , y}; SetConsoleCursorPosition(h,c);
}

void atualizarCursor(){
  gotoXY(buf_g.getPosX(), buf_g.getPosY());
}

void _direita(){
  buf_g.irParaDireita();
  pilha_acoes.push(direita);
  atualizarCursor();
}

void _desfazer(){
  Acao a = pilha_acoes.pop();
  acoes_opostas_g[a]();
}

void _esquerda(){
  buf_g.irParaEsquerda();
  pilha_acoes.push(esquerda);
  atualizarCursor();
}

void _descer(){
  buf_g.descerLinha();
  pilha_acoes.push(descer);
  atualizarCursor();
}

void _subir(){
  buf_g.subirLinha();
  pilha_acoes.push(subir);
  atualizarCursor();
}

void _breakLine(){
  buf_g.inserirLinha();
  cout << '\n';
}

void _deletarCaracter(){
  buf_g.deletarADireita();
  atualizarCursor();
  cout << " ";
  atualizarCursor();
}

void _default(unsigned short int i){
  buf_g.inserirCaracter(i);
  pilha_acoes.push(inserirCaracter);
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
  //ofn.Flags        = OFN_DONTADDTORECENT;

//  if (GetSaveFileName( &ofn )){
    return filename;
  //}

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

void _exit(){
  quit = 1;
}

void _begin()
{
    buf_g.voltarAoInicioDaLinha();
    atualizarCursor();
}

void _pgDown()
{
    buf_g.descerPagina();
    atualizarCursor();
}

void _pgUp()
{
    buf_g.subirPagina();
    atualizarCursor();
}

void _end()
{
    buf_g.irAoFimDaLinha();
    atualizarCursor();
}

int main(int argc, char **args){
  kr_g = KeyResolver(&_default);
  kr_g[19] = &_salvar;
  kr_g[8] = &_deletarCaracter;
  kr_g[13] = &_breakLine;
  kr_g[10] = &_esquerda;
  kr_g[11] = &_descer;
  kr_g[9] = &_subir;
  kr_g[12] = &_direita;
  kr_g[26] = &_desfazer;
  kr_g[17] = &_exit;
  kr_g[14] = &_end;
  kr_g[2]  = &_begin;
  kr_g[28]  = &_pgDown;
  kr_g[1] = &_pgUp;
  buf_g = Buffer();

  pilha_acoes = PilhaAcao();
  acoes_opostas_g = AcoesRelacionais();

  acoes_opostas_g[subir] = &_descer;
  acoes_opostas_g[descer] = &_subir;
  acoes_opostas_g[esquerda] = &_direita;
  acoes_opostas_g[direita] = &_esquerda;
  acoes_opostas_g[inserirCaracter] = &_deletarCaracter;

  while(!quit){
    kr_g.resolver();
  }

  return 0;
}

