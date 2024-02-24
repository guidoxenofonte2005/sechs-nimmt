
typedef struct elementoPilha *Pilha;

Pilha *criarPilha();
int inserirPilha(Pilha *, struct carta);
int removerPilha(Pilha *, struct carta *);
void embaralhar(Pilha *);
int tamanhoPilha(Pilha *);
