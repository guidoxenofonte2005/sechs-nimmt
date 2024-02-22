#include <stdio.h>
#include <stdlib.h>
#include "uni_game.h"
#include "lista.h"
#include "pilha.h"
#include "fila.h"

#define FILAS 4

int main()
{
    Lista * Mao;
    Fila ** Mesa;
    Pilha * Baralho;
    Lista ** ColecaoJogadores;

    int temp_pcount = 0;
    printf("Qtd: ");
    scanf("%d", &temp_pcount);

    ColecaoJogadores = (Lista **) malloc(sizeof(Lista *));
    for (int i = 0; i < temp_pcount; i++) {
        ColecaoJogadores[i] = criar();
    }

    return 0;
}
