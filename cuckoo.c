// GRR20195689 Eduardo Vudala Senoski

#include "cuckoo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void mustAlloc(void* ptr, const char* description){
    if (!ptr){
        printf("Couldn't alloc memory for %s", description);
        exit(1);
    }
}

int hash1(int k, int m){
    return k % m;
}

int hash2(int k, int m){
    return (int) (m * (k*0.9 - (int) (k * 0.9)));
}

int* newKey(int key){
    int* newK = malloc(sizeof(int));
    *newK = key;
    return newK;
}

struct cuckoo* newCuckoo(int m){
    struct cuckoo* newC = malloc(sizeof(struct cuckoo));
    mustAlloc(newC, "newC");

    newC->table1 = malloc(sizeof(int*) * SIZE);
    mustAlloc(newC->table1, "table1");

    newC->table2 = malloc(sizeof(int*) * SIZE);
    mustAlloc(newC->table2, "table2");

    return newC;
}

int search(int key, struct cuckoo* cHash){
    // Caso esteja na table1
    int pos = hash1(key, SIZE);
    if(cHash->table1[pos] != NULL && *cHash->table1[pos] == key)
        return pos;

    // Caso esteja na table2
    pos = hash2(key, SIZE);
    if(cHash->table2[pos] != NULL && *cHash->table2[pos] == key)
        return pos;

    // Caso não esteja em nenhuma table
    return -1;
}

void insert(int key, struct cuckoo* cHash){
    // Caso a chave ja exista em alguma tabela
    if(search(key, cHash) >= 0)
        return;

    // Se a posicao hash1(key) estiver livre em table1
    int pos = hash1(key, SIZE);
    if(cHash->table1[pos] == NULL){ 
        cHash->table1[pos] = newKey(key);
        return;
    }

    // Do contrário escreve a velha key em table2 e a nova em table1
    cHash->table2[hash2(*cHash->table1[pos], SIZE)] = cHash->table1[pos];
    cHash->table1[pos] = newKey(key);
}

void delete(int key, struct cuckoo* cHash){
    // Se estiver na table1 a deleta
    int pos = hash1(key, SIZE);
    if(cHash->table1[pos] != NULL && *cHash->table1[pos] == key){ 
        free(cHash->table1[pos]);
        cHash->table1[pos] = NULL;
        return;
    }

    // Se estiver na table2 a deleta
    pos = hash2(key, SIZE);
    if(cHash->table2[pos] != NULL && *cHash->table2[pos] == key){ 
        free(cHash->table2[pos]);
        cHash->table2[pos] = NULL;
        return;
    }
}

// Recupera a chave da string
int getKey(char* str){
    char aux[12];
    strcpy(aux, str);
    return atoi(strtok(aux, ","));
}

// Função auxiliar do qsort
static int compare(const void* a, const void* b) {
    int aux1 = getKey(*(char**)a);
    int aux2 = getKey(*(char**)b);
    if (aux1 <  aux2) return -1;
    if (aux1 > aux2) return 1;
    return 0;
}
  
void sort(char** arr, int n) { 
    qsort(arr, n, sizeof(char*), compare); 
}

void navigate(struct cuckoo* cHash){
    // Navega pelas duas tables e armazena os elementos processados em um vetor
    int max_size = 50;
    char** words = malloc(sizeof(char*) * SIZE * 2);
    int j = 0;
    for(int i = 0; i < SIZE; i++){
        // Se há um elemento nessa posição, o encaixa em uma string e guarda em words
        if(cHash->table1[i] != NULL){
            char* aux = malloc(sizeof(char) * max_size);
            mustAlloc(aux, "aux");
            snprintf(aux, max_size, "%i,T1,%i", *cHash->table1[i], i);
            words[j++] = aux;
        }
        
        // Se há um elemento nessa posição, o encaixa em uma string e guarda em words
        if(cHash->table2[i] != NULL){
            char* aux = malloc(sizeof(char) * max_size);
            mustAlloc(aux, "aux");
            snprintf(aux, max_size, "%i,T2,%i", *cHash->table2[i], i);
            words[j++] = aux;
        }
    }
    // Faz um sort nesse vetor e imprime os elementos ordenados
    sort(words, j);
    j = 0;
    while(words[j] != NULL)
        printf("%s\n", words[j++]);
}