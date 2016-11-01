#include "Editor.h";

using namespace std;

static void _direita(){
  buf.irParaDireita();
  pilha_acoes.push(direita);
  //...
  //Acao a = pilha_acoes.pop();
  //acoes[a]();
}

static void _desfazer(){
  Acao a = pilha_acoes.pop();
  acoes[a]();
}

static void _esquerda(){
  buf.irParaEsquerda();
}

static void _descer(){
  buf.descerLinha();
}

static void _subir(){
  buf.subirLinha();
}

// static void _inserirCaracter(){
//   // buf.inserirCaracter();
// }

static void _deletarCaracter(){
  buf.deletarADireita();
}

static void _default(unsigned short int i){
  buf.inserirCaracter((char) i);
}

Editor::Editor(){

  kr = KeyResolver(&_default);
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
  this->kr = KeyResolver(oso.kr);
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
