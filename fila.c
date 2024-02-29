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
        if (fd->fim == NULL) {
            fd->inicio = novo;
        }
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
        *cartaRemovida = aux->carta;
        free(aux);
        return 1;
    }
}

int acessarFila(Fila *fd, int pos, struct carta *cartaAcessada)
{
    if (vaziaFila(fd))
        return 0;
    else {
        ElementoFila *aux = fd->inicio;
        for (int i = 0; i < pos; i++) {
            aux = aux->prox;
        }
        *cartaAcessada = aux->carta;
        return 1;
    }
}

int exibirFila(Fila *fd)
{
    int res, bois;
    struct carta cartaAcessada;

    if (vaziaFila(fd))
        return 0;
    for (int j = 0; j < tamanhoFila(fd); j++) {
        printf(".--=-=--.");
    }
    printf("\n");
    for (int j = 0; j < tamanhoFila(fd); j++) {
        res = acessarFila(fd, j, &cartaAcessada);
        printf("|");
        bois = cartaAcessada.bois;
        switch (bois)
        {
        case 1:
            printf("   %%   |");
            break;
        case 2:
            printf("  %% %%  |");
            break;
        case 3:
            printf(" %% %% %% |");
            break;
        case 4:
            printf("%% %% %% %%|");
            break;
        case 5:
            printf(" %% %% %% |");
            break;
        case 6:
            printf(" %% %% %% |");
            break;
        case 7:
            printf("%% %% %% %%|");
            break;
        default:
            break;
        }
    }
    printf("\n");
    for (int j = 0; j < tamanhoFila(fd); j++) {
        res = acessarFila(fd, j, &cartaAcessada);
        printf("|");
        bois = cartaAcessada.bois;
        switch (bois)
        {
        case 5:
            printf("  %% %%  |");
            break;
        case 6:
            printf(" %% %% %% |");
            break;
        case 7:
            printf(" %% %% %% |");
            break;
        default:
            printf("       |");
            break;
        }
    }
    printf("\n");
    for (int j = 0; j < tamanhoFila(fd); j++) {
        res = acessarFila(fd, j, &cartaAcessada);
        if (cartaAcessada.numero < 10)
            printf("|   %d   |", cartaAcessada.numero);
        else if (cartaAcessada.numero >= 10 && cartaAcessada.numero < 100)
            printf("|   %d  |", cartaAcessada.numero);
        else
            printf("|  %d  |", cartaAcessada.numero);
    }
    printf("\n");
    for (int j = 0; j < tamanhoFila(fd); j++) {
        res = acessarFila(fd, j, &cartaAcessada);
        printf("|");
        bois = cartaAcessada.bois;
        switch (bois)
        {
        case 5:
            printf("  %% %%  |");
            break;
        case 6:
            printf(" %% %% %% |");
            break;
        case 7:
            printf(" %% %% %% |");
            break;
        default:
            printf("       |");
            break;
        }
    }
    printf("\n");
    for (int j = 0; j < tamanhoFila(fd); j++) {
        res = acessarFila(fd, j, &cartaAcessada);
        printf("|");
        bois = cartaAcessada.bois;
        switch (bois)
        {
        case 1:
            printf("   %%   |");
            break;
        case 2:
            printf("  %% %%  |");
            break;
        case 3:
            printf(" %% %% %% |");
            break;
        case 4:
            printf("%% %% %% %%|");
            break;
        case 5:
            printf(" %% %% %% |");
            break;
        case 6:
            printf(" %% %% %% |");
            break;
        case 7:
            printf("%% %% %% %%|");
            break;
        default:
            break;
        }
    }
    printf("\n");
    for (int j = 0; j < tamanhoFila(fd); j++)
        printf("\'--=-=--\'");
    printf("\n\n");

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
