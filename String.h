#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED
class String
{
    private:
        char* conteudo;

    public:
        String();
        String(unsigned int len);
        ~String();
        char charAt(unsigned int pos) const;
        int length() const;
        void deleta(unsigned int posIni, unsigned int posFinal);
        void deletaCharAt(unsigned int pos);
        void insere(unsigned int pos, char c);
        void replacer(unsigned int pos, char c);
        char* toString() const;


};


#endif // STRING_H_INCLUDED
