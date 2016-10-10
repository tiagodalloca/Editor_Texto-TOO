#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "String.h"
using namespace std;

int main()
{
    char* r = (char*)malloc(3*sizeof(char));
    r = "123";
    printf("%c", *(r + 2));
    return 0;
}
