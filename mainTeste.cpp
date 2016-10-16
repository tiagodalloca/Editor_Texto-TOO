#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "String.h"
#include "ListaCircularDupla.h"
#include "ListaCD.h"
using namespace std;

int main()
{
//
//    String s;
//    s = "abc";
//    printf("tamanho : %i \n",s.length());
//    printf("String : %s \n", s.toString());
//    s.deletaCharAt(1);
//    printf("String Renovada : %s \n",s.toString());
//
//char* ponte = new char[5];
//*(ponte) = '2';
//printf("%c\n\n\n",ponte[0]);
//char* pont = (char*)malloc(5*sizeof(char));
//*(pont) = 'a';
//*(pont + 1) = 'b';
//*(pont + 2) = 'c';
//*(pont + 3) = 'd';
//*(pont + 4) = 'e';
//printf("%c%c%c%c%c\n\n",*(pont),*(pont +1),*(pont +2),*(pont +3),*(pont +4));
//String s(pont);
//printf("%s\n\n",s.toString());
//s.insere(2,'z');
//printf("%s\n\n",s.toString());
//s.deleta(1,2);
//printf("%s\n\n",s.toString());
//s.append('f');
//printf("%s\n\n",s.toString());
//
//String s2 = "acdefg";
//if(s < s2)
//    printf("valor menor  \n\n");
//else
//    printf("valores nao menor \n\n");

ListaCD<int> lcd;
lcd.insira(2);
printf("%i",lcd.infoAtual());


return 0;
}
