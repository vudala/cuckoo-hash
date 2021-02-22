#define DELETED -2147483648 // O maior int
#define SIZE 11 

struct cuckoo {
    int** table1;
    int** table2;
};

void mustAlloc(void* ptr, const char* description);

// Cria uma nova cuckoo hash
struct cuckoo* newCuckoo();

// Insere a key
void insert(int key, struct cuckoo* cHash);

// Deleta a key
void delete(int key, struct cuckoo* cHash);

// Imprime todas as keys inseridas em ordem
void navigate(struct cuckoo* cHash);