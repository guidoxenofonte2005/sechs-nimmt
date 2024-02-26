#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"
#include "pilha.h"
#include "fila.h"
#include "uni_game.h"
#include "game_code.h"

#define ROUNDS 10

int main()
{
    srand(time(0));

    // variables
    Lista * Mao;
    Fila ** Mesa;
    Pilha * Baralho;
    Lista ** ColecaoJogadores;
    int jogadores = 0;
    int *pontos;

    // CONFIG / DEBUG FUNCTIONS
    //debugColor();
    config();
    title();

    // GAME STARTING POINT
    do {
        printf("Qtd de jogadores: ");
        fflush(stdin);
        scanf("%d", &jogadores);
    } while (jogadores < 2 || jogadores > 10);

    system("cls");

    pontos = (int *) malloc(jogadores * sizeof(int));
    for (int i = 0; i < jogadores; i++)
        pontos[i] = 0;

    for (int i = 0; i < ROUNDS; i++) {
        presentTurn(i+1);
        Mao = criar();
        Baralho = criarPilha();
        RunGame(Mao, Mesa, Baralho, ColecaoJogadores, jogadores, pontos);
    }

    system("cls");

    return 0;
}
