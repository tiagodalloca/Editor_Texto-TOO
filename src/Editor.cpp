#include "Editor.h";

using namespace std;

typedef enum{
  esquerda, direita,
  inserirCaracter,
  descer, subir,
  novaLinha
}Acao;

typedef map<Acao, void(*)()> Acoes;

Buffer buf;
KeyResolver kr([&buf](unsigned short int i)->void{
      buf.inserirCaracter((char) i);
    });
Acoes acoes;
Pilha<Acoes> pilha_acoes;
char parar;

static void _direita(){
  buf.irParaDireita();
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

static void _inserirCaracter(){
  // buf.inserirCaracter();
}

static void _deletarCaracter(){
  buf.deletarADireita();
}

Editor::Editor(){
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
