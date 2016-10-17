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
        void alteraCont(char* outro);
        void append(char c);
        bool operator >(String oso);
        bool operator >=(String oso);
        bool operator ==(String oso);
        bool operator <(String oso);
        bool operator <=(String oso);
        bool operator !=(String oso);

        String& operator=(const String& oso);
        String(const String& oso);


};


#endif // STRING_H_INCLUDED
