// GRR20195689 Eduardo Vudala Senoski

#define DELETED -2147483648
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