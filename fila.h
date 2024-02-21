
typedef struct fila *Fila;

Fila *criarFila();
int inserirFila(Fila *, struct carta);
int removerFila(Fila *, struct carta *);
int acessar(Fila *, struct carta *);
int exibirFila(Fila *);
int tamanhoFila(Fila *);

