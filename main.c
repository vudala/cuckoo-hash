#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cuckoo.h"

#define MAXWORDSIZE 20

int main(){

    struct cuckoo* cuckoo = newCuckoo();

    char* aux = malloc(MAXWORDSIZE);
    mustAlloc(aux, "aux string");

    char* op = NULL; // Qual operação executar
    int key; // Com qual valor executar

    while(fgets(aux, MAXWORDSIZE, stdin)){
        op = strtok(aux, " ");
        key = atoi(strtok(NULL, " "));
        if(!strcmp(op, "i"))
            insert(key, cuckoo);
        else if(!strcmp(op, "r"))
            delete(key, cuckoo);
    }

    navigate(cuckoo);

    return 0;
}