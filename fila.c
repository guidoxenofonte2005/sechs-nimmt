#include <stdio.h>
#include <stdlib.h>
#include "uni_game.h"
#include "fila.h"

/**
  * criarFila - OK
  * inserirFila - OK
  * removerFila - OK
  * acessar - OK
  * exibirFila -
  * tamanhoFila - OK
  */
struct elementoFila
{
    Carta carta;
    struct elementoFila *prox;
};

typedef struct elementoFila ElementoFila;

struct fila
{
    struct elementoFila *inicio;
    struct elementoFila *fim;
};

// aux functions

int vaziaFila(Fila *fd)
{
    if (fd == NULL)
        return 1;
    else if (fd->inicio == NULL)
        return 1;
    else
        return 0;
}

// main functions

Fila *criarFila()
{
    Fila *fd;
    fd = (Fila *) malloc(sizeof(Fila));
    if (fd != NULL) {
        fd->inicio = NULL;
        fd->fim = NULL;
    }
    return fd;
}

int inserirFila(Fila *fd, struct carta novaCarta)
{
    if (fd == NULL)
        return 0;
    else {
        ElementoFila *novo = (ElementoFila *) malloc(sizeof(ElementoFila));
        if (novo == NULL)
            return 0;
        novo->carta = novaCarta;
        novo->prox = NULL;
        if (fd->fim == NULL)
            fd->inicio = novo;
        else
            fd->fim->prox = novo;
        fd->fim = novo;
        return 1;
    }
}

int removerFila(Fila *fd, struct carta *cartaRemovida)
{
    if (vaziaFila(fd))
        return 0;
    else {
        ElementoFila *aux = fd->inicio;
        fd->inicio = fd->inicio->prox;
        if (fd->inicio == NULL)
            fd->fim = NULL;
        free(aux);
        return 1;
    }
}

int acessarFila(Fila *fd, struct carta *cartaAcessada)
{
    if (vaziaFila(fd))
        return 0;
    else {
        *cartaAcessada = fd->inicio->carta;
        return 1;
    }
}

int exibirFila(Fila *fd)
{
    if (vaziaFila(fd))
        return 0;
    struct carta temp;
    for (int i = 0; i < tamanhoFila(fd); i++) {
        int res = acessarFila(fd, &temp);
        if (temp.numero < 10)
            printf("[  %d]", temp.numero);
        else if (temp.numero >= 10 && temp.numero < 100)
            printf("[ %d]", temp.numero);
        else
            printf("[%d]", temp.numero);

        if (i != tamanhoFila(fd)-1)
            printf("->");
    }
    return 1;
}

int tamanhoFila(Fila *fd)
{
    if (vaziaFila(fd))
        return 0;
    int cont = 0;
    ElementoFila *aux = fd->inicio;
    while (aux != NULL) {
        cont++;
        aux = aux->prox;
    }
    return cont;

}
