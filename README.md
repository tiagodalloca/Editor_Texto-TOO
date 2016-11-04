# Editor de texto

Super editor de texto básico feito em C++

## Modelagem

### `String`

Vai representar cada linha do buffer (uma string = uma linha)

### `ListaCD`

Vai representar um conjunto de linhas (`String`s)

### `Buffer`

Guardará o texto que estiver sendo editado

### `KeyResolver`

Vai "resolver" as teclas pressionadas pelo usuário, fazendo com que as funções certas sejam executadas.

### `Editor`

O Editor conterá:
- `KeyResolver`
- `Buffer`
- `Métodos`
    
Terá que fazer o meio de entre o `Buffer` e o `KeyResolver`

## Descrição MALIGNA

### String

- Terá tamanho inicial dado pelo construtor
- Terá a capacidade crescimento automático
- O vetor de char que a representa internamente,
  vai ser acessado sem o uso de [], ou seja, com
   ponteiros
- Métodos:
  . charAt(unsigned int posicao)
  . no lugar de compareTo, quero operator<,
    operator<=, operator>, operator>=, operator==
    e operator!=
  . no lugar de concat, quero operator+
  . length
  . append(char)
  . delete(unsigned int posIni, unsigned int posFinal)
  . deleteCharAt(unsigned int posicao)
  . insert(unsigned int posicao, char oque)
  . replace(unsigned int posicao, char oque)
  . toString()
  . claro que vai precisar de um construtor de
    copia, operator= de cópia e de um destrutor

### ListaDuplamenteLigadaCircular de String

Vai ter a ideia de posicao atual dada por um
ponteiro que, a principio, apontará para o
primeiro nó, mas, que depois, poderá mudar de
lugar via métodos que faremos

- Métodos:
 . insira(String linha) // na posicao atual
 . insiraDepois(String linha) // da posicao atual
 . remova() // linha da posicao atual
 . removaDepois() // linha depois da posicao atual
 . infoAtual() // retorna o String do nó atual
 . avance() // avança circularmente a posicao atual
 . retroceda() // retrocede circularmente a posicao atual
 . claro que vai precisar de um construtor de
   copia, operator= de cópia e de um destrutor

### Pilha

- Empilhará ações (Acao será uma classe SECRETA
  definida por voces)
- Quando, ao empilhar, não couber, remover a base
  da pilha, e realizar entao o empilhamento
- Métodos:
 . Construtor para dimensionar
 . empilhe
 . desempilhe
 . espie (retorna o que tem no topo sem desempilhar)
 . cheia
 . vazia
 . claro que vai precisar de um construtor de
   copia, operator= de cópia e de um destrutor

**DICA**: BAIXE E USE A BIBLIOTECA conio.h

---

## COMANDOS

### MÍNIMOS:
[ ] sobe linha (normalmente, seta)
[ ] desce linha (normalmente, seta)
[ ] vai para a esquerda (normalmente, seta)
[ ] vai para a direita (normalmente, seta)
[ ] sobe página (normalmente, PAGE UP)
[ ] desce página (normalmente, PAGE DOWN)
[ ] vai para o inicio da linha (normalmente, HOME)
[ ] vai para o fim da linha (normalmente, END)
[ ] apaga char no cursor (normalmente, DELETE)
[ ] apaga char antes do cursor (normalmente, BACKSPACE)
[ ] desfazer (normalmente, CONTROL Z)
[ ] refazer (normalmente, CONTROL Y)
[ ] salvar (normalmente, CONTROL S)
[ ] salvar como
  perguntar se quer sobrescrever arquivo existente
[ ] sair (normalmente, ESC)
 perguntar se quer sair sem salvar

### OPCIONAIS:
[ ] marcar inicio de selecao
[ ] marcar fim de selecao
[ ] mover a selecao para a posicao do cursor
[ ] copiar a selecao para a posicao do cursor
[ ] procurar
[ ] substituir
[ ] etc


