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
PilhaAcao pilha_reacoes;
AcoesRelacionais acoes_opostas_g;
char quit;
bool insertAtivo;

void _default(unsigned short int i);
void _backspace();
void _descer();
void _subir();
void _esquerda();
void _direita();
void _breakLine();

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

void _desfazerDescer(void **args, DesfazerRefazer dr){
  _subir();
  int *x = (int*) args[0];
  buf_g.setX(*x);
  atualizarCursor();
  if(dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }
}

void _desfazerSubir(void **args, DesfazerRefazer dr){
  _descer();
  int *x = (int*) args[0];
  buf_g.setX(*x);
  atualizarCursor();
  if(dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }  
}

void _desfazerEsquerda(void **args, DesfazerRefazer dr){
  _direita();
  if(dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }
}

void _desfazerDireita(void **args, DesfazerRefazer dr){
  _esquerda();
  if(dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }  
}

void _desfazerInserir(void **args, DesfazerRefazer dr){
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
  
  if(dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }
}

void _desfazerBackDel(void **args, DesfazerRefazer dr){
  char *i = (char*) args[0];
  bool aux = insertAtivo;
  
  insertAtivo = true;
  _default(*i);

  insertAtivo = aux;
  
  if(dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }
}

void _desfazerFrontDel(void **args, DesfazerRefazer dr){
  char *i = (char*) args[0];
  bool aux = insertAtivo;

  insertAtivo = true;
  _default(*i);

  buf_g.irParaEsquerda();
  atualizarCursor();

  insertAtivo = aux; 
  
  if(dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }
}


void _desfazerNovaLinha(void **args, DesfazerRefazer dr){
  // aqui é a parte difícil do bagui
}

void _desfazerExcluirLinha(void **args, DesfazerRefazer dr){
  _breakLine();
//   if(dr == desfazer){
//     AcaoEncapsulada *a = pilha_acoes.pop();
//     pilha_reacoes.push(a);
//   } breakline não está empilhando nada ainda
}


void _desfazerExcluirLinhaEmbaixo(void **args, DesfazerRefazer dr){
  _breakLine();
//   if(dr == desfazer){
//     AcaoEncapsulada *a = pilha_acoes.pop();
//     pilha_reacoes.push(a);
//   } breakline não está empilhando nada ainda
}

void _desfazer(){
  if (pilha_acoes.getQuantos() > 0){
    AcaoEncapsulada *a = pilha_acoes.pop();
    acoes_opostas_g[a->acao](a->args, desfazer);
    free(a);
  }
}

void _refazer(){
  if (pilha_reacoes.getQuantos() > 0){
    AcaoEncapsulada *a = pilha_reacoes.pop();
    acoes_opostas_g[a->acao](a->args, refazer);
    free(a);
  }
}

void _direita(){
  void **args = (void**) malloc(0);
  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = direita;
  a->args = args;
  pilha_acoes.push(a);
  buf_g.irParaDireita();
  atualizarCursor();
}


void _esquerda(){
  void **args = (void**) malloc(0);
  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = esquerda;
  a->args = args;
  pilha_acoes.push(a);
  buf_g.irParaEsquerda();
  atualizarCursor();
}

void _descer(){
  if(buf_g.getPosY() < buf_g.quantasLinhas() - 1){
    void **args = (void**) malloc(sizeof(int*));
    args[0] = (void*) malloc(sizeof(int));
    *((int*)args[0]) = buf_g.getPosX();
    AcaoEncapsulada *a = new AcaoEncapsulada;
    a->acao = descer;
    a->args = args;
    pilha_acoes.push(a);
    buf_g.descerLinha();
    atualizarCursor();
  }
}

void _subir(){
  if(buf_g.getPosY() > 0){
    void **args = (void**) malloc(sizeof(int*));
    args[0] = (void*) malloc(sizeof(int));
    *((int*)args[0]) = buf_g.getPosX();
    AcaoEncapsulada *a = new AcaoEncapsulada;
    a->acao = subir;
    a->args = args;
    pilha_acoes.push(a);
    buf_g.subirLinha();
    atualizarCursor();
  }
}

void _breakLine(){
  for (int i = buf_g.getPosX(); i < buf_g.tamanhoLinha(); i++)
    cout << ' ';
  atualizarCursor();
  char* c = buf_g.getRestoLinha();
  MyString* ms = new MyString(c);
  buf_g.inserirLinhaDepois(ms);
  atualizarCursor();
  insline();
  atualizarCursor();
  cout << ms->toString();
  atualizarCursor();
	
  // falta empilhar uma acao aqui!
  // criar um desfazer!
  // criar
}


void _delete(){
  int len = buf_g.tamanhoLinha();
  int y = buf_g.getPosY() + 1;
  int x = buf_g.getPosX() + 1;

  if (x-1 == len && y <= buf_g.quantasLinhas()){
    buf_g.descerLinha();
    int slen = buf_g.tamanhoLinha();
    MyString s = buf_g.deletarLinha();
    buf_g.inserirCaracteresNoFinal(s.toString());
    
    movetext(1,
             y + 1,
             slen + 1,
             y + 1,
             len + 1,
             y);

    gotoXY(0, y);
    for (int i = 0; i<slen; i++)
      cout << ' ';

    atualizarCursor();
    
    void **args =(void**)malloc(0);
    AcaoEncapsulada *a = new AcaoEncapsulada;
    a->acao = excluirLinha;
    a->args = args;
    pilha_acoes.push(a);
  }
    else{
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
  }}
}

void _backspace()
{
  int len = buf_g.tamanhoLinha();
  int y = buf_g.getPosY() + 1;
  int x = buf_g.getPosX() + 1;

  if (x == 1 && y != 1){
    MyString s = buf_g.deletarLinha();
    int lenDeCima = buf_g.tamanhoLinha();
    buf_g.inserirCaracteresNoFinal(s.toString());
    
    movetext(1,
             y,
             len + 1,
             y,
             lenDeCima + 1,
             y - 1);

    gotoXY(0, y - 1);
    for (int i = 0; i<len; i++)
      cout << ' ';

    buf_g.setX(lenDeCima);
    atualizarCursor();

    void **args =(void**)malloc(0);
    AcaoEncapsulada *a = new AcaoEncapsulada;
    a->acao = excluirLinha;
    a->args = args;
    pilha_acoes.push(a);
  }
  else{
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

      void **args = (void**)malloc(sizeof(char*));
      args[0] = (void*)malloc(sizeof(char));

      *((char*)args[0]) = c;

      AcaoEncapsulada *a = new AcaoEncapsulada;
      a->acao = backdel;
      a->args = args;

      pilha_acoes.push(a);
    }
  }
}

void _default(unsigned short int i){
  bool voltar = false;
  int x = buf_g.getPosX();
  int y = buf_g.getPosY();
  if (buf_g.tamanhoLinha() == buf_g.tamanhoMax() - 1)
    {

      if (buf_g.getPosX() == buf_g.tamanhoLinha()){
        _breakLine();
      }
      else{
        buf_g.setX(buf_g.tamanhoMax() - 2);
        atualizarCursor();
        char c = buf_g.charADireita();
        _delete();
        buf_g.setX(x);
        buf_g.setY(y);
        atualizarCursor();
        _default(i);
        buf_g.setX(buf_g.tamanhoLinha());
        _breakLine();
        atualizarCursor();
        i = c;
        voltar = true;
      }		
    }

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

  if (voltar){
    buf_g.setY(y);
    buf_g.setX(x+1);
    atualizarCursor();
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

void config(){
  kr_g = KeyResolver(&_default);
  kr_g[19] = &_salvar;   //Ctrl + 's'
  kr_g[8] = &_backspace; //Backspace
  kr_g[13] = &_breakLine;//Enter
  kr_g[10] = &_esquerda; //Ctrl + 'j'
  kr_g[11] = &_descer;   //Ctrl + 'k'
  kr_g[9] = &_subir;     //Ctrl + 'i'
  kr_g[12] = &_direita;  //Ctrl + 'l'
  kr_g[26] = &_desfazer; //Ctrl + 'z'
  kr_g[25] = &_refazer;  //Ctrl + 'y'
  kr_g[17] = &_exit;     //Ctrl + 'q'
  kr_g[2]  = &_begin;    //Ctrl + 'b'
  kr_g[14] = &_end;      //Ctrl + 'n'
  kr_g[1] = &_pgUp;      //Ctrl + 'a'
  kr_g[28]  = &_pgDown;  //Ctrl + '\'
  kr_g[15] = &_delete;   //Ctrl + 'o'
  kr_g[16] = &_insert;   //Ctrl + 'p'
  buf_g = Buffer(80);

  pilha_acoes = PilhaAcao();
  pilha_reacoes = PilhaAcao();
  acoes_opostas_g = AcoesRelacionais();
  insertAtivo = true;
  
  acoes_opostas_g[subir] = &_desfazerSubir;
  acoes_opostas_g[descer] = &_desfazerDescer;
  acoes_opostas_g[esquerda] = &_desfazerEsquerda;
  acoes_opostas_g[direita] = &_desfazerDireita;
  acoes_opostas_g[inserirCaracter] = &_desfazerInserir;
  acoes_opostas_g[backdel] = &_desfazerBackDel;
  acoes_opostas_g[frontdel] = &_desfazerFrontDel;
  acoes_opostas_g[novaLinha] = &_desfazerNovaLinha;
  acoes_opostas_g[excluirLinha] = &_desfazerExcluirLinha;
  acoes_opostas_g[excluirLinhaEmbaixo] =
    &_desfazerExcluirLinhaEmbaixo;
}

int main(int argc, char **args){
  config();
  
  while(!quit){
    kr_g.resolver();
  }
  return 0;
}
