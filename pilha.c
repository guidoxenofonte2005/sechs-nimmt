#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "uni_game.h"
#include "pilha.h"

#define CARDS 104

/**
  * criar - OK
  * inserir - OK
  * remover - OK
  * embaralhar -
  * tamanhoPilha - OK
  */

struct elementoPilha
{
    struct carta carta;
    struct elemento *prox;
};

typedef struct elementoPilha ElementoPilha;

// aux functions

int vaziaPilha(Pilha *pe)
{
    if (pe == NULL)
        return 1;
    else if (*pe == NULL)
        return 1;
    else
        return 0;
}

// main functions

Pilha *criarPilha()
{
    Pilha *pe;
    pe = (Pilha *) malloc(sizeof(Pilha));

    if (pe != NULL)
        *pe = NULL;

    return pe;
}

int inserirPilha(Pilha *pe, struct carta novaCarta)
{
    if (pe == NULL)
        return 0;
    else {
        ElementoPilha *novo = (ElementoPilha *) malloc(sizeof(ElementoPilha));
        if (novo == NULL)
            return 0;
        novo->carta = novaCarta;
        novo->prox = *pe;
        *pe = novo;
        return 1;
    }
}

int removerPilha(Pilha *pe, struct carta *cartaRemovida)
{
    if (vaziaPilha(pe))
        return 0;
    else {
        ElementoPilha *aux = *pe;
        *cartaRemovida = aux->carta;
        *pe = aux->prox;
        free(aux);
    }
    return 1;
}

void embaralhar(Pilha *pe)
{
    if (vaziaPilha(pe))
        return 0;
    else {
        for (int i = 0; i < CARDS; i++) {
            int random = rand() % (CARDS - 1);
            ElementoPilha *ant = NULL;
            ElementoPilha *aux = *pe;

            for (int j = 0; j < random; j++) {
                ant = aux;
                aux = aux->prox;
            }

            ElementoPilha *pos = aux;
            ElementoPilha *fim = pos->prox;

            if (fim->prox != NULL) {
                while (fim->prox != NULL) {
                    pos = fim;
                    fim = fim->prox;
                }
                if (random != 0) {
                    fim->prox = aux->prox;
                    ant->prox = fim;
                    pos->prox = aux;
                    aux->prox = NULL;
                }
                else {
                    fim->prox = aux->prox;
                    pos->prox = aux;
                    aux->prox = NULL;
                    *pe = fim;
                }
            }
            else {
                ant->prox = fim;
                fim->prox = aux;
                aux->prox = NULL;
            }
        }
    }

    return 1;
}

int tamanhoPilha(Pilha *pe)
{
    if (vaziaPilha(pe))
        return 0;
    else {
        ElementoPilha *aux = *pe;
        int cont = 0;
        while (aux != NULL) {
            cont++;
            aux = aux->prox;
        }
        return cont;
    }
}
