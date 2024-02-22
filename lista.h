
typedef struct elemento * Lista;

Lista *criar();
int inserirOrdenado(Lista *, struct carta);
int removerIndice(Lista *, int);
int acessarIndice(Lista *, int, struct carta *);
int exibirLista(Lista *);
int quantidade(Lista *);
