#include "Pilha.h"
#include "KeyResolver.h"
#include "Buffer.h"
#include "Misc.h"

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include "conio2.h"

KeyResolver kr_g;
Buffer buf_g;
PilhaAcao pilha_acoes;
AcoesRelacionais acoes_opostas_g;
char quit;
bool insertAtivo;

void _default(unsigned short int i);
void _backspace();

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

void _voltar(void **args){
  int *x = (int*) args[0];
  int *y = (int*) args[1];
  gotoXY(*x, *y);
  buf_g.setX(*x);
  buf_g.setY(*y);
  free(x);
  free(y);
}

void _desfazerInserir(void **args){
  bool* insert = (bool*)args[0];
  if (*insert)
    _backspace();
  else{
    char* c = (char*)args[1];

    bool aux = insertAtivo;
    insertAtivo = false;

    buf_g.irParaEsquerda();
    atualizarCursor();
    _default(*c);
    insertAtivo = aux;

    buf_g.irParaEsquerda();
    atualizarCursor();
  }
  
  AcaoEncapsulada *a = pilha_acoes.pop();
  free(a->args);
  free(a);
  
  free(args);
}

void _desfazerBackDel(void **args){
  char *i = (char*) args[0];
  bool aux = insertAtivo;
  
  insertAtivo = true;
  _default(*i);

  insertAtivo = aux;
  
  AcaoEncapsulada *a = pilha_acoes.pop();
  free(a->args);
  free(a);
  free(i);
  free(args);
}

void _desfazerFrontDel(void **args){
  char *i = (char*) args[0];
  bool aux = insertAtivo;

  insertAtivo = true;
  _default(*i);

  buf_g.irParaEsquerda();
  atualizarCursor();

  insertAtivo = aux; 
  
  AcaoEncapsulada *a = pilha_acoes.pop();
  free(a->args);
  free(a);
  free(i);
  free(args);
}


void _desfazerNovaLinha(void **args){
  // aqui é a parte difícil do bagui
}

void _desfazer(){
  if (pilha_acoes.getQuantos() > 0){
    AcaoEncapsulada *a = pilha_acoes.pop();
    acoes_opostas_g[a->acao](a->args);
    free(a);
  }
}


void _direita(){
  void **args = (void**) malloc(sizeof(int*)*2);
  int x = buf_g.getPosX();
  int y = buf_g.getPosY();

  args[0] = (void*) malloc(sizeof(int));
  args[1] = (void*) malloc(sizeof(int));


  *((int*) args[0]) = x;
  *((int*) args[1]) = y;

  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = direita;
  a->args = args;
  
  pilha_acoes.push(a);
  buf_g.irParaDireita();
  atualizarCursor();
}


void _esquerda(){
  void **args = (void**) malloc(sizeof(int*)*2);
  int x = buf_g.getPosX();
  int y = buf_g.getPosY();

  args[0] = (void*) malloc(sizeof(int));
  args[1] = (void*) malloc(sizeof(int));
  
  *((int*) args[0]) = x;
  *((int*) args[1]) = y;

  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = esquerda;
  a->args = args;
  
  pilha_acoes.push(a);
  buf_g.irParaEsquerda();
  atualizarCursor();
}

void _descer(){
  if(buf_g.getPosY() < buf_g.quantasLinhas() - 1){
    void **args = (void**) malloc(sizeof(int*)*2);
    int x = buf_g.getPosX();
    int y = buf_g.getPosY();

    args[0] = (void*) malloc(sizeof(int));
    args[1] = (void*) malloc(sizeof(int));
  
    *((int*) args[0]) = x;
    *((int*) args[1]) = y;

    AcaoEncapsulada *a = new AcaoEncapsulada;
    a->acao = subir;
    a->args = args;
  
    pilha_acoes.push(a);
    
    buf_g.descerLinha();
    atualizarCursor();
  }
}

void _subir(){
  if(buf_g.getPosY() > 0){
    void **args = (void**) malloc(sizeof(int*)*2);
    int x = buf_g.getPosX();
    int y = buf_g.getPosY();

    args[0] = (void*) malloc(sizeof(int));
    args[1] = (void*) malloc(sizeof(int));
  
    *((int*) args[0]) = x;
    *((int*) args[1]) = y;

    AcaoEncapsulada *a = new AcaoEncapsulada;
    a->acao = subir;
    a->args = args;
  
    pilha_acoes.push(a);
      
    buf_g.subirLinha();
    atualizarCursor();
  }
}

void _breakLine(){
  buf_g.inserirLinha();
  cout << '\n';
  
}


void _delete(){
int len = buf_g.tamanhoLinha();
  int y = buf_g.getPosY() + 1;
  int x = buf_g.getPosX() + 1;

  //Deleta o caracter no buffer
  char c = buf_g.deletarADireita();

  if (c){
    movetext(x + 1,
             y,
             len + 1,
             y,
             x,
             y);

    void **args = (void**) malloc(sizeof(char*));
    args[0] = (void*) malloc(sizeof(char));

    *((char*)args[0]) = c;
    
    AcaoEncapsulada *a = new AcaoEncapsulada;
    a->acao = frontdel;
    a->args = args;

    pilha_acoes.push(a);
  }
}

void _backspace()
{
  int len = buf_g.tamanhoLinha();
  int y = buf_g.getPosY() + 1;
  int x = buf_g.getPosX() + 1;

  //Deleta o caracter no buffer
  char c = buf_g.deletarAEsquerda();

  if (c){
    movetext(x,
             y,
             len + 1,
             y,
             x - 1,
             y);
      
    //Põe o cursor no lugar certo
    atualizarCursor();

    void **args = (void**) malloc(sizeof(char*));
    args[0] = (void*) malloc(sizeof(char));

    *((char*)args[0]) = c;
    
    AcaoEncapsulada *a = new AcaoEncapsulada;
    a->acao = backdel;
    a->args = args;

    pilha_acoes.push(a);
  }    
}

void _default(unsigned short int i){
  char c = 0;
  if(insertAtivo){
    int len = buf_g.tamanhoLinha();
    int y = buf_g.getPosY() + 1;
    int x = buf_g.getPosX() + 1;

    buf_g.inserirCaracter(i);

    movetext(x,
             y,
             len + 1,
             y,
             x + 1,
             y);
    gotoXY(x - 1, y - 1);

  }
  else {
    c = buf_g.deletarADireita();
    buf_g.inserirCaracter(i);
   }

  void **args = (void**) malloc(sizeof(bool*) + sizeof(char*));
  args[0] = (void*)malloc(sizeof(bool));
  args[1] = (void*)malloc(sizeof(char));
  *((bool*)args[0]) = insertAtivo;
  *((char*)args[1]) = c;

  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = inserirCaracter;
  a->args = args;

  pilha_acoes.push(a);

  cout << (char)i;
}

char* _saveFileDialog(){
  char *filename = (char*) malloc(MAX_PATH*sizeof(char));
  // char filename[MAX_PATH];
  OPENFILENAME ofn;
  ZeroMemory( &ofn,      sizeof( ofn ) );
  ZeroMemory( filename,  sizeof( filename ) );
  ofn.lStructSize  = sizeof( ofn );
  ofn.hwndOwner    = NULL;
  ofn.lpstrFilter  = "Text Files\0*.txt\0Any File\0*.*\0";
  ofn.lpstrFile    = filename;
  ofn.nMaxFile     = MAX_PATH;
  ofn.lpstrTitle   = "Selecione um arquivo";
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

void _insert()
{
  if(insertAtivo)
    insertAtivo = false;
  else
    insertAtivo = true;
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
  kr_g[19] = &_salvar;   //Ctrl + 's'
  kr_g[8] = &_backspace; //Backspace
  kr_g[13] = &_breakLine;//Enter
  kr_g[10] = &_esquerda; //Ctrl + 'j'
  kr_g[11] = &_descer;   //Ctrl + 'k'
  kr_g[9] = &_subir;     //Ctrl + 'i'
  kr_g[12] = &_direita;  //Ctrl + 'l'
  kr_g[26] = &_desfazer; //Ctrl + 'z'
  kr_g[17] = &_exit;     //Ctrl + 'q'
  kr_g[2]  = &_begin;    //Ctrl + 'b'
  kr_g[14] = &_end;      //Ctrl + 'n'
  kr_g[1] = &_pgUp;      //Ctrl + 'a'
  kr_g[28]  = &_pgDown;  //Ctrl + '\'
  kr_g[15] = &_delete;   //Ctrl + 'o'
  kr_g[16] = &_insert;   //Ctrl + 'p'
  buf_g = Buffer();

  pilha_acoes = PilhaAcao();
  acoes_opostas_g = AcoesRelacionais();
  insertAtivo = true;
  
  acoes_opostas_g[subir] = &_voltar;
  acoes_opostas_g[descer] = &_voltar;
  acoes_opostas_g[esquerda] = &_voltar;
  acoes_opostas_g[direita] = &_voltar;
  acoes_opostas_g[inserirCaracter] = &_desfazerInserir;
  acoes_opostas_g[backdel] = &_desfazerBackDel;
  acoes_opostas_g[frontdel] = &_desfazerFrontDel;
  acoes_opostas_g[novaLinha] = &_desfazerNovaLinha;

  while(!quit){
    kr_g.resolver();
  }
  return 0;
}

