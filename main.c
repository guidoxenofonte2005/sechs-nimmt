#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"
#include "pilha.h"
#include "fila.h"
#include "uni_game.h"

#define ROUNDS 10

int main()
{
    // variables
    Lista * Mao;
    Fila ** Mesa;
    Pilha * Baralho;
    Lista ** ColecaoJogadores;
    int jogadores = 0;
    int *pontos;

    config();
    title();
    srand(time(NULL));

    Mao = criar();
    Baralho = criarPilha();

    do {
    printf("Qtd de jogadores: ");
    fflush(stdin);
    scanf("%d", &jogadores);
    } while (jogadores < 2 || jogadores > 10);

    iniciarRound(Mao, Mesa, Baralho, ColecaoJogadores, jogadores);

    return 0;
}
