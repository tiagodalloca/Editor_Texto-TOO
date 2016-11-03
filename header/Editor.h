#include <stdlib.h>
#include <map>

#include "Pilha.h"
#include "Buffer.h"
#include "KeyResolver.h"

using namespace std;

class Editor{
  
  typedef enum{
    esquerda, direita,
    inserirCaracter,
    descer, subir,
    novaLinha
  }Acao;

  typedef std::map<Acao, void(Editor::*)()> Acoes;

public:
  Editor();
  ~Editor();
  Editor(const Editor&);
  void iniciar();
  
  void _deletarCaracter();
  void _default(unsigned short int i);
  void _direita();
  void _desfazer();
  void _esquerda();
  void _descer();
  void _subir();
  
private:
  void loop();
  Buffer buf;
  KeyResolver<Editor> kr;
  Acoes acoes;
  Pilha<Acao> pilha_acoes;
  char parar;

};
