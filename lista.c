#include <stdio.h>
#include <stdlib.h>
#include "uni_game.h"
#include "lista.h"

/**
    criar OK
    inserir ordenado OK
    acessar indice OK
    remover indice OK
    exibir
    quantidade = tamanho OK
*/
struct elemento {
    Carta carta;
    struct elemento *prox;
};

typedef struct elemento Elemento;

// aux functions

int vazia(Lista *ldse)
{
    if (ldse == NULL)
        return 1;
    else if (*ldse == NULL)
        return 1;
    else
        return 0;
}

// main functions

Lista *criar()
{
    Lista *ldse;

    ldse = (Lista *) malloc(sizeof(Lista));
    if (ldse != NULL)
        *ldse = NULL;
    return ldse;
}

int inserirOrdenado(Lista *ldse, struct carta novaCarta)
{
    if (ldse == NULL)
        return 0;
    Elemento *novo = (Elemento *) malloc(sizeof(Elemento));
    if (novo == NULL)
        return 0;
    novo->carta = novaCarta;
    if (vazia(ldse) || (*ldse)->carta.numero > novo->carta.numero) {
        novo->prox = *ldse;
        *ldse = novo;
    }
    else {
        Elemento *ant = *ldse;
        Elemento *aux = ant->prox;
        while (aux != NULL && aux->carta.numero < novo->carta.numero) {
            ant = aux;
            aux = aux->prox;
        }
        ant->prox = novo;
        novo->prox = aux;
    }
    return 1;
}

int removerIndice(Lista *ldse, int i, struct carta * cartaRemovida)
{
    if (vazia(ldse))
        return 0;
    else if (i < 0)
        return 0;
    else {
        int cont = 0;
        Elemento *ant = NULL;
        Elemento *aux = *ldse;
        if (i == 0) {
            *ldse = aux->prox;
            *cartaRemovida = aux->carta;
            free(aux);
        }
        else {
            while (aux != NULL && i != cont) {
                cont++;
                ant = aux;
                aux = aux->prox;
            }
            if (aux == NULL)
                return 0;
            ant->prox = aux->prox;
            *cartaRemovida = aux->carta;
            free(aux);
        }
    }
    return 1;
}

int acessarIndice(Lista *ldse, int i, struct carta *carta)
{
    if (vazia(ldse))
        return 0;
    else if (i < 0)
        return 0;
    else {
        int cont = 0;
        Elemento *aux = *ldse;
        while (aux != NULL && i != cont) {
            cont++;
            aux = aux->prox;
        }
        if (aux == NULL)
            return 0;
        *carta = aux->carta;
        return 1;
    }
}

int exibirLista(Lista *ldse)
{
    struct carta cartaAcessada;
    int res, bois, espacos;

    if (vazia(ldse))
        return 0;


    espacos = ((10 - quantidade(ldse)) * 4);
    for (int i = 0; i < espacos; i++)
        printf(" ");

    for (int j = 0; j < quantidade(ldse); j++) {
        printf(".--=-=--.");
    }


    printf("\n");
    for (int i = 0; i < espacos; i++)
        printf(" ");
    for (int j = 0; j < quantidade(ldse); j++) {
        res = acessarIndice(ldse, j, &cartaAcessada);
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
    for (int i = 0; i < espacos; i++)
        printf(" ");
    for (int j = 0; j < quantidade(ldse); j++) {
        res = acessarIndice(ldse, j, &cartaAcessada);
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
    for (int i = 0; i < espacos; i++)
        printf(" ");
    for (int j = 0; j < quantidade(ldse); j++) {
        res = acessarIndice(ldse, j, &cartaAcessada);
        if (cartaAcessada.numero < 10)
            printf("|   %d   |", cartaAcessada.numero);
        else if (cartaAcessada.numero >= 10 && cartaAcessada.numero < 100)
            printf("|   %d  |", cartaAcessada.numero);
        else
            printf("|  %d  |", cartaAcessada.numero);
    }
    printf("\n");
    for (int i = 0; i < espacos; i++)
        printf(" ");
    for (int j = 0; j < quantidade(ldse); j++) {
        res = acessarIndice(ldse, j, &cartaAcessada);
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
    for (int i = 0; i < espacos; i++)
        printf(" ");
    for (int j = 0; j < quantidade(ldse); j++) {
        res = acessarIndice(ldse, j, &cartaAcessada);
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
    for (int i = 0; i < espacos; i++)
        printf(" ");
    for (int j = 0; j < quantidade(ldse); j++)
        printf("\'--=-=--\'");
    printf("\n");

    for (int i = 0; i < espacos; i++)
        printf(" ");

    for (int i = 1; i <= quantidade(ldse); i++)
        printf("   (%d)   ", i);
    printf("\n");
    return 1;
}

int quantidade(Lista *ldse)
{
    if (vazia(ldse))
        return 0;
    int cont = 0;
    Elemento *aux = *ldse;
    while (aux != NULL) {
        cont++;
        aux = aux->prox;
    }
    return cont;
}
