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
bool insertAtivo = false;

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
  // buf_g.setX();
  // buf_g.setY(); 
}

void _desfazerInserir(void **args){
  buf_g.deletarADireita();
  atualizarCursor();
  cout << " ";
  atualizarCursor();
}

void _desfazerBackDel(void **args){
  char *i = (char*) args[0];
  buf_g.inserirCaracter(*i);
  cout << *i;
}

void _desfazerFrontDel(void **args){
  char *i = (char*) args[0];
  buf_g.inserirCaracter(*i);
  cout << *i;
}

void _desfazer(){
  if (pilha_acoes.getQuantos() > 0){
    AcaoEncapsulada *a = pilha_acoes.pop();
    acoes_opostas_g[a->acao](a->args);
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
  int y = buf_g.getPosY();
  int x = buf_g.getPosX();
  gotoXY(0,y);
  for(int i = 0;i<len;i++)
    cout << " ";

  char c = buf_g.deletarADireita();
  gotoXY(0,y);
  cout << buf_g.getLinha(buf_g.getPosY());
  gotoXY(x,y);

  void **args = (void**) malloc(sizeof(char*));
  args[0] = (void*) malloc(sizeof(char));

  *((char*)args[0]) = c;
    
  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = frontdel;
  a->args = args;

  pilha_acoes.push(a);
}

void _backspace()
{
    int len = buf_g.tamanhoLinha();
    int y = buf_g.getPosY();
    int x = buf_g.getPosX();
    gotoXY(0,y);

    for(int i = 0;i<len;i++)
      cout << " ";
    
    char c = buf_g.deletarAEsquerda();
    gotoXY(0,y);
    cout << buf_g.getLinha(buf_g.getPosY());
    gotoXY(x-1,y);

    void **args = (void**) malloc(sizeof(char*));
    args[0] = (void*) malloc(sizeof(char));

    *((char*)args[0]) = c;
    
    AcaoEncapsulada *a = new AcaoEncapsulada;
    a->acao = backdel;
    a->args = args;

    pilha_acoes.push(a);
}

void _default(unsigned short int i){
  if(!insertAtivo){
    int len = buf_g.tamanhoLinha();
    int y = buf_g.getPosY();
    int x = buf_g.getPosX();
    gotoXY(0,y);

    for(int i = x;i<len+1;i++)
      cout << " ";

    buf_g.inserirCaracter(i);
    gotoXY(0,y);
    cout << buf_g.getLinha(buf_g.getPosY());
    gotoXY(x+1,y);

    void **args = {};

    AcaoEncapsulada *a = new AcaoEncapsulada;
    a->acao = inserirCaracter;
    a->args = args;
  
    pilha_acoes.push(a);
  }
  else {
    buf_g.inserirCaracter(i);
    
    void **args = {};

    AcaoEncapsulada *a = new AcaoEncapsulada;
    a->acao = inserirCaracter;
    a->args = args;
      
    pilha_acoes.push(a);
    cout << (char) i;
   }
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

  acoes_opostas_g[subir] = &_voltar;
  acoes_opostas_g[descer] = &_voltar;
  acoes_opostas_g[esquerda] = &_voltar;
  acoes_opostas_g[direita] = &_voltar;
  acoes_opostas_g[inserirCaracter] = &_desfazerInserir;
  acoes_opostas_g[backdel] = &_desfazerBackDel;
  acoes_opostas_g[frontdel] = &_desfazerFrontDel;

  while(!quit){
    kr_g.resolver();
  }
  return 0;
}

