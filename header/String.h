#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED
class String
{
    private:
        char* conteudo;

    public:
        String();
        String(unsigned int len);
        String(char* contNovo);
        ~String();
        int length() const;
        void deleta(unsigned int posIni, unsigned int posFinal);
        void deletaCharAt(unsigned int pos);
        void insere(unsigned int pos, char c);
        char& operator[](unsigned int pos) const;
        char* toString() const;
        void operator=(char *c);


};


#endif // STRING_H_INCLUDED
