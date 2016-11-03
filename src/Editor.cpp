#include "Editor.h"

using namespace std;

void Editor::_direita(){
  buf.irParaDireita();
  pilha_acoes.push(direita);
  //...
  //Acao a = pilha_acoes.pop();
  //acoes[a]();
}

void Editor::_desfazer(){
  Acao a = pilha_acoes.pop();
  acoes[a]();
}

void Editor::_esquerda(){
  buf.irParaEsquerda();
}

void Editor::_descer(){
  buf.descerLinha();
}

void Editor::_subir(){
  buf.subirLinha();
}

// static void Editor::_inserirCaracter(){
//   // buf.inserirCaracter();
// }

void Editor::_deletarCaracter(){
  buf.deletarADireita();
}

void Editor::_default(unsigned short int i){
  buf.inserirCaracter((char) i);
}

Editor::Editor(){

  kr = KeyResolver<Editor>(&_default);
  kr[26] = &_desfazer; // control-z desfaz

  acoes = Acoes();
  acoes[esquerda] = &_direita;
  acoes[direita] = &_esquerda;
  acoes[descer] = &_subir;
  acoes[subir] = &_descer;
  acoes[inserirCaracter] = &_deletarCaracter;
  acoes[novaLinha] = NULL;
  
  buf = Buffer();
  parar = 0;
}


Editor::~Editor(){
}

Editor::Editor(const Editor& oso){
  // this->acoes = Pilha<Acoes>(oso.acoes);
  this->kr = KeyResolver<Editor>(oso.kr);
  this->parar = oso.parar;
}

void Editor::iniciar(){
  loop();
}

void Editor::loop(){
  while(!parar){
    kr.resolver();
  }
}
