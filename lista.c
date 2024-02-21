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
    struct carta carta;
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

int removerIndice(Lista *ldse, int i)
{
    if vazia(ldse)
        return 0;
    else if (i < 0)
        return 0;
    else {
        int cont = 0;
        Elemento *ant = NULL;
        Elemento *aux = *ldse;
        while (aux != NULL && i != cont) {
            cont++;
            ant = aux;
            aux = aux->prox;
        }
        if (aux == NULL)
            return 0;
        ant->prox = aux->prox;
        free(aux);
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
