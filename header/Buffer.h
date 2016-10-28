#ifndef BUFFER
#define BUFFER

#include "MyString.h"
#include "ListaCD.h"

class Buffer{
public:
    Buffer();
    Buffer(ListaCD<MyString*>* novaLista);
    std::string linhasAsString();
    void subirLinha();
    void descerLinha();
    void irParaEsquerda();
    void irParaDireita();
    void inserirCaracter(char);
    void inserirLinha(MyString* linha);
    void deletarADireita();
    void deletarAEsquerda();
    char* getLinha(unsigned int);
private:
    ListaCD<MyString*>* linhas;
    unsigned int coluna;
    int tam = 0;
};

#endif
