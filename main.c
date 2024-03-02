#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"
#include "pilha.h"
#include "fila.h"
#include "uni_game.h"
#include "game_code.h"

#define ROUNDS 10
#define MIN_PLAYERS 2
#define MAX_PLAYERS 10
#define INT_PLACEHOLDER 4

int main()
{
    srand(time(0));

    // variables
    Lista * Mao;
    Fila ** Mesa;
    Pilha * Baralho;
    Lista ** ColecaoJogadores;
    int jogadores, winner;
    int *pontos;
    int play;

    // CONFIG / DEBUG FUNCTIONS
    //debugColor();
    config();
    credits();
    do {
        title();
        play = titleOptions();
    } while (play != 1);


    // GAME STARTING POINT
    jogadores = INT_PLACEHOLDER;
    do {
        system("cls");
        if (jogadores < MIN_PLAYERS || jogadores > MAX_PLAYERS) {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            color(4);
            printf("\t\t\t\t     INSERÇÃO INVÁLIDA!\n");
            color(8);
            printf("\t\t\t\t    Número de jogadores: ");
        }
        else {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            color(8);
            printf("\t\t\t\t    Número de jogadores: ");
        }
        fflush(stdin);
        scanf("%d", &jogadores);
    } while (jogadores < MIN_PLAYERS || jogadores > MAX_PLAYERS);

    system("cls");

    pontos = (int *) malloc(jogadores * sizeof(int));
    for (int i = 0; i < jogadores; i++)
        pontos[i] = 0;

    loadingScreen();
    system("cls");

    for (int i = 0; i < ROUNDS; i++) {
        presentTurn(i+1);
        if (i != 0)
            showPoints(pontos, jogadores);
        Mao = criar();
        Baralho = criarPilha();
        RunGame(Mao, Mesa, Baralho, ColecaoJogadores, jogadores, pontos);
    }

    winner = countPoints(pontos, jogadores);

    victoryScreen(winner, pontos, jogadores);

    Sleep(3000);

    return 0;
}
