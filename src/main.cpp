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
bool podeDesempilhar;
bool podeAdicionar;

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

void talvezEsvaziarCY(){
  if (podeDesempilhar){
    while(pilha_reacoes.getQuantos() > 0){
      pilha_reacoes.pop();
      //delete[] a->args;
      //delete a;
      // switch(a){
      // case novaLinha:
      //   delete[][] n
      //   break
      // }
    }
  }
}
void atualizarCursor(){
  gotoXY(buf_g.getPosX(), buf_g.getPosY());
} 

void _desfazerDescer(void **args, DesfazerRefazer dr){

  podeDesempilhar = false;
  
  _subir();
  int *x = (int*) args[0];
  buf_g.setX(*x);
  atualizarCursor();
  if(dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }

  podeDesempilhar = true;
}

void _desfazerSubir(void **args, DesfazerRefazer dr){
  podeDesempilhar = false;
  
  _descer();
  int *x = (int*) args[0];
  buf_g.setX(*x);
  atualizarCursor();
  if(dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }

  podeDesempilhar = true;
}

void meioEnd(int i)
{
  void **args = (void**)malloc(sizeof(int*));
  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = meioEndi;
  pilha_acoes.push(a);
  buf_g.setX(i);
  atualizarCursor();
}

void _desfazerEnd(void** args, DesfazerRefazer dr)
{
  int i = *((int*)args[0]);
  meioEnd(i);
  if (dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  } 
}

void meioup(int x, int y)
{
  void **args = (void**)malloc(sizeof(int*));
  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = meioUp;
  pilha_acoes.push(a);
  buf_g.setY(y);
  buf_g.setX(x);
  atualizarCursor();
}

void meiodown(int x, int y)
{
  void **args = (void**)malloc(sizeof(int*));
  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = meioDown;
  pilha_acoes.push(a);
  buf_g.setY(y);
  buf_g.setX(x);
  atualizarCursor();
}

void meioHome(int i)
{
  void **args = (void**)malloc(sizeof(int*));
  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = meioHomi;
  pilha_acoes.push(a);
  buf_g.setX(i);
  atualizarCursor();
}

void _desfazerHome(void** args, DesfazerRefazer dr)
{
  int i = *((int*)args[0]);
  meioHome(i);
  if (dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }
}

void _desfazerUp(void** args, DesfazerRefazer dr)
{
  podeDesempilhar = false;
  int x = *((int*)args[0]);
  int y = *((int*)args[1]);
  meioup(x,y);
  if (dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }

  podeDesempilhar = true;
}

void _desfazerDown(void** args, DesfazerRefazer dr)
{
  podeDesempilhar = false;

  int x = *((int*)args[0]);
  int y = *((int*)args[1]);
  meiodown(x, y);
  if (dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }

  podeDesempilhar = true;
}

void _desfazerEsquerda(void **args, DesfazerRefazer dr){
  podeDesempilhar = false;
  
  _direita();
  if(dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }

  podeDesempilhar = true;
}

void _desfazerDireita(void **args, DesfazerRefazer dr){
  podeDesempilhar = false;
  
  _esquerda();
  if(dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }

  podeDesempilhar = true;
}

void _deleteSemEmpilhar(){
  talvezEsvaziarCY();

  int len = buf_g.tamanhoLinha();
  int y = buf_g.getPosY() + 1;
  int x = buf_g.getPosX() + 1;

  if (x - 1 == len && y <= buf_g.quantasLinhas()){

    gotoXY(x - 1, y);
    delline();

    buf_g.descerLinha();
    int slen = buf_g.tamanhoLinha();
    MyString s = buf_g.deletarLinha();
    buf_g.inserirCaracteresNoFinal(s.toString());

    atualizarCursor();
    cout << s.toString();
    atualizarCursor();

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


    }
  }
}


void puxarParaCima()
{
  int x = buf_g.getPosX();
  int y = buf_g.getPosY();
  buf_g.setX(x - 1);
  _deleteSemEmpilhar();
  buf_g.setX(0);
  buf_g.setY(y + 1);
  char c = buf_g.charADireita();
  _deleteSemEmpilhar();
  buf_g.setY(y);
  buf_g.setX(buf_g.tamanhoLinha());
  atualizarCursor();
  buf_g.inserirCaracter(c);
  cout << c;
  buf_g.setX(x - 1);
  buf_g.setY(y);
  atualizarCursor();
}
void _desfazerInserir(void **args, DesfazerRefazer dr){
  bool* insert = (bool*)args[0];
  bool podeDeletar = *((bool*)args[2]);
  podeDesempilhar = false;

  if (podeDeletar)
    {
      puxarParaCima();
    }
  else
    {
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
    }

  podeDesempilhar = true;
  
  if (dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }
}


void _breakLineSemEmpilhar(){
  talvezEsvaziarCY();


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


}


void _desfazerBackDel(void **args, DesfazerRefazer dr){
  podeDesempilhar = false;
  
  char *i = (char*) args[0];
  bool aux = insertAtivo;
  
  insertAtivo = true;
  _default(*i);

  insertAtivo = aux;
  
  if(dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }

  podeDesempilhar = true;
}

void _desfazerFrontDel(void **args, DesfazerRefazer dr){

  podeDesempilhar = false;
  
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

  podeDesempilhar = true;
}


void _desfazerNovaLinha(void **args, DesfazerRefazer dr){

  podeDesempilhar = false;

  _backspace();
  if (dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }

  podeDesempilhar = true;
}

void _desfazerExcluirLinha(void **args, DesfazerRefazer dr){

  podeDesempilhar = false;
  
  _breakLine();
  if(dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }

  podeDesempilhar = true;
}


void _desfazerExcluirLinhaEmbaixo(void **args, DesfazerRefazer dr){
  _breakLine();
  if(dr == desfazer){
    AcaoEncapsulada *a = pilha_acoes.pop();
    pilha_reacoes.push(a);
  }
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
  talvezEsvaziarCY();
  
  void **args = (void**) malloc(0);
  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = esquerda;
  a->args = args;
  pilha_acoes.push(a);
  buf_g.irParaEsquerda();
  atualizarCursor();
}





void _descer(){
  talvezEsvaziarCY();
  
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
  talvezEsvaziarCY();
  
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

void _breakLine2(){
  talvezEsvaziarCY();


  for (int i = buf_g.getPosX(); i < buf_g.tamanhoLinha(); i++)
    cout << ' ';
  atualizarCursor();
  char* c = buf_g.getRestoLinha();

  void **args = (void**)malloc(sizeof(char*));
  args[0] = (void*)malloc(sizeof(char));

  strcpy((char*)args[0], c);
  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = novaLinha;
  a->args = args;

  pilha_acoes.push(a);

  MyString* ms = new MyString(c);
  buf_g.inserirLinhaDepois(ms);
  atualizarCursor();
  insline();
  atualizarCursor();
  cout << ms->toString();
  atualizarCursor();


}

void _breakLine(){
  talvezEsvaziarCY();

  
  for (int i = buf_g.getPosX(); i < buf_g.tamanhoLinha(); i++)
    cout << ' ';
  atualizarCursor();
  char* c = buf_g.getRestoLinha();

  void **args = (void**)malloc(sizeof(char*));
  args[0] = (void*)malloc(sizeof(char));

  strcpy((char*)args[0], c);
  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = novaLinha;
  a->args = args;

  pilha_acoes.push(a);

  MyString* ms = new MyString(c);
  buf_g.inserirLinhaDepois(ms);
  atualizarCursor();
  insline();
  atualizarCursor();
  cout << ms->toString();
  atualizarCursor();


}

void parteDoBackspace()
{
  char c = buf_g.charADireita();
  _deleteSemEmpilhar();
  buf_g.subirLinha();
  buf_g.setX(buf_g.tamanhoLinha());
  atualizarCursor();
  buf_g.inserirCaracter(c);
  cout << c;

  atualizarCursor();


}


void _backspaceSemEmpilhar()
{
  talvezEsvaziarCY();

  int len = buf_g.tamanhoLinha();
  int y = buf_g.getPosY() + 1;
  int x = buf_g.getPosX() + 1;

  if (x == 1 && y != 1){

    buf_g.subirLinha();
    unsigned int slen = buf_g.tamanhoLinha();
    buf_g.descerLinha();

    delline();
    MyString s = buf_g.deletarLinha();
    buf_g.setX(buf_g.tamanhoLinha());
    atualizarCursor();
    char* c = s.toString();
    buf_g.inserirCaracteres(c);
    cout << c;

    buf_g.setX(slen);
    atualizarCursor();

    buf_g.setY(y - 2);
    buf_g.setX(slen);
    atualizarCursor();
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
      //atualizarCursor();
      if (buf_g.tamanhoLinha() + 2 == buf_g.tamanhoMax() && buf_g.getPosY() < buf_g.quantasLinhas() - 1){
        buf_g.setY(y);
        if (buf_g.tamanhoLinha() > 0){
          buf_g.setY(y - 1);
          int x = buf_g.getPosX();
          int y = buf_g.getPosY();
          buf_g.setY(y + 1);
          buf_g.setX(0);
          atualizarCursor();
          parteDoBackspace();
        }
      }
    }
  }
}

void _delete(){
  talvezEsvaziarCY();

  int len = buf_g.tamanhoLinha();
  int y = buf_g.getPosY() + 1;
  int x = buf_g.getPosX() + 1;

  if (x - 1 == len && y < buf_g.quantasLinhas()){
    buf_g.setY(y);
    buf_g.setX(0);
    atualizarCursor();
    _backspace();


  }
  else{
    //Deleta o caracter no buffer
    char c = buf_g.charADireita();

    if (c){
      buf_g.irParaDireita();
      int x = buf_g.getPosX();
      int y = buf_g.getPosY();
      _backspaceSemEmpilhar();
      buf_g.setX(x-1);
      buf_g.setY(y);
      atualizarCursor();
      void **args = (void**)malloc(sizeof(char*));
      args[0] = (void*)malloc(sizeof(char));

      *((char*)args[0]) = c;

      AcaoEncapsulada *a = new AcaoEncapsulada;
      a->acao = frontdel;
      a->args = args;

      pilha_acoes.push(a);
    }
  }
}



void _backspace()
{
  talvezEsvaziarCY();
  
  int len = buf_g.tamanhoLinha();
  int y = buf_g.getPosY() + 1;
  int x = buf_g.getPosX() + 1;

  if (x == 1 && y != 1){

    buf_g.subirLinha();
    unsigned int slen = buf_g.tamanhoLinha();
    buf_g.descerLinha();

    delline();
    MyString s = buf_g.deletarLinha();    
    buf_g.setX(buf_g.tamanhoLinha());
    atualizarCursor();
    char* c = s.toString();
    buf_g.inserirCaracteres(c);
    cout << c;

    buf_g.setX(slen);
    atualizarCursor();

    void **args =(void**)malloc(0);
    AcaoEncapsulada *a = new AcaoEncapsulada;
    a->acao = excluirLinha;
    a->args = args;
    pilha_acoes.push(a);
    
    buf_g.setY(y - 2);
    buf_g.setX(slen);
    atualizarCursor();
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
      //atualizarCursor();
      if (buf_g.tamanhoLinha() + 2 == buf_g.tamanhoMax() && buf_g.getPosY() < buf_g.quantasLinhas()-1)
        {
          buf_g.setY(y);
          if (buf_g.tamanhoLinha() > 0)
            {
              buf_g.setY(y - 1);
              int x = buf_g.getPosX();
              int y = buf_g.getPosY();
              buf_g.setY(y + 1);
              buf_g.setX(0);
              atualizarCursor();
              parteDoBackspace();
            }
        
        }

      void **args = (void**)malloc(sizeof(char*));
      args[0] = (void*)malloc(sizeof(char));

      *((char*)args[0]) = c;

      AcaoEncapsulada *a = new AcaoEncapsulada;
      a->acao = backdel;
      a->args = args;

      pilha_acoes.push(a);

      buf_g.setY(y - 1);
      buf_g.setX(x - 2);
      atualizarCursor();
    }
  }
}

void _default(unsigned short int i){

  talvezEsvaziarCY();
  
  bool voltar = false;
  int x = buf_g.getPosX();
  int y = buf_g.getPosY();
  if (buf_g.tamanhoLinha() == buf_g.tamanhoMax() - 1)
    {

      if (buf_g.getPosX() == buf_g.tamanhoLinha()){
        _breakLine2();
      }
      else{

        buf_g.setX(buf_g.tamanhoMax() - 2);
        atualizarCursor();
        char c = buf_g.charADireita();
        _deleteSemEmpilhar();
        buf_g.setX(x);
        buf_g.setY(y);
        atualizarCursor();
        _default(i);
        buf_g.setX(buf_g.tamanhoLinha());
        if (!podeAdicionar)
          _breakLineSemEmpilhar();
        else
          {
            buf_g.setY(y + 1);
            buf_g.setX(0);
          }
        atualizarCursor();
        i = c;
        voltar = true;
        podeAdicionar = true;
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

  void **args = (void**) malloc(sizeof(bool*) + sizeof(char*) + sizeof(bool*));
  args[0] = (void*)malloc(sizeof(bool));
  args[1] = (void*)malloc(sizeof(char));
  args[2] = (void*)malloc(sizeof(bool));
  *((bool*)args[0]) = insertAtivo;
  *((char*)args[1]) = c;
  *((bool*)args[2]) = voltar;



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

void _abrir(char *filename){
  FILE *f = fopen(filename, "r");
  if (f){
    buf_g.deletarLinha();
    
    char linha[80];
    while (fgets(linha, 80, f) != NULL){
      char *c;
      for(c = linha; *c != '\0'; c++){
        if (*c == '\n'){
          *c = '\0';
          break;
        }
      }

      buf_g.inserirLinha(new MyString(linha));
      cout << linha << '\n';
    }

    buf_g.setY(0);
    atualizarCursor();
    
    delete linha;
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
  talvezEsvaziarCY();
  
  void **args = (void**)malloc(sizeof(char*));
  args[0] = (void*)malloc(sizeof(int));

  *((int*)args[0]) = buf_g.getPosX();

  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = homi;
  a->args = args;
  pilha_acoes.push(a);

  buf_g.voltarAoInicioDaLinha();
  atualizarCursor();
}

void _pgDown()
{
  talvezEsvaziarCY();
  
  void **args = (void**)malloc(sizeof(char*));
  args[0] = (void*)malloc(sizeof(int));
  args[1] = (void*)malloc(sizeof(int));

  *((int*)args[0]) = buf_g.getPosX();
  *((int*)args[1]) = buf_g.getPosY();

  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = down;
  a->args = args;
  pilha_acoes.push(a);

  buf_g.descerPagina();
  atualizarCursor();
}

void _pgUp()
{
  talvezEsvaziarCY();
  
  void **args = (void**)malloc(sizeof(char*));
  args[0] = (void*)malloc(sizeof(int));
  args[1] = (void*)malloc(sizeof(int));

  *((int*)args[0]) = buf_g.getPosX();
  *((int*)args[1]) = buf_g.getPosY();
  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = up;
  a->args = args;
  pilha_acoes.push(a);

  buf_g.subirPagina();
  atualizarCursor();
}

void _desfazerMeioDown(void** args, DesfazerRefazer dr)
{
  _pgDown();
}

void _desfazerMeioUp(void** args, DesfazerRefazer dr)
{
  _pgUp();
}

void _desfazerMeioEnd(void** args, DesfazerRefazer dr)
{

  void **args2 = (void**)malloc(sizeof(char*));
  args2[0] = (void*)malloc(sizeof(int));

  *((int*)args2[0]) = buf_g.getPosX();

  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = endi;
  a->args = args2;
  pilha_acoes.push(a);

  buf_g.irAoFimDaLinha();
  atualizarCursor();
}

void _desfazerMeioHome(void** args, DesfazerRefazer dr)
{

  void **args2 = (void**)malloc(sizeof(char*));
  args2[0] = (void*)malloc(sizeof(int));

  *((int*)args2[0]) = buf_g.getPosX();

  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = homi;
  a->args = args2;
  pilha_acoes.push(a);

  buf_g.voltarAoInicioDaLinha();
  atualizarCursor();
}

void _end()
{
  talvezEsvaziarCY();
  
  void **args = (void**)malloc(sizeof(char*));
  args[0] = (void*)malloc(sizeof(int));

  *((int*)args[0]) = buf_g.getPosX();

  AcaoEncapsulada *a = new AcaoEncapsulada;
  a->acao = endi;
  a->args = args;
  pilha_acoes.push(a);

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
  podeDesempilhar = true;
  podeAdicionar = true;
  
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
  acoes_opostas_g[endi] = &_desfazerEnd;
  acoes_opostas_g[homi] = &_desfazerHome;
  acoes_opostas_g[meioEndi] = &_desfazerMeioEnd;
  acoes_opostas_g[meioHomi] = &_desfazerMeioHome;
  
  acoes_opostas_g[up] = &_desfazerUp;
  acoes_opostas_g[down] = &_desfazerDown;
  acoes_opostas_g[meioUp] = &_desfazerMeioUp;
  acoes_opostas_g[meioDown] = &_desfazerMeioDown;
}

int main(int argc, char **args){
  config();

  if (argc > 1){
    _abrir(args[1]);
  }
  
  while(!quit){
    kr_g.resolver();
  }
  return 0;
}
