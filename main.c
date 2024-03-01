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
    jogadores = 4;
    do {
        system("cls");
        if (jogadores < 2 || jogadores > 10) {
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
    } while (jogadores < 2 || jogadores > 10);

    system("cls");

    pontos = (int *) malloc(jogadores * sizeof(int));
    for (int i = 0; i < jogadores; i++)
        pontos[i] = 0;

    loadingScreen();
    system("cls");

    //for (int i = 0; i < ROUNDS; i++) {
        //presentTurn(i+1);
//        if (i != 0)
//            showPoints(pontos, jogadores);
        Mao = criar();
        Baralho = criarPilha();
        RunGame(Mao, Mesa, Baralho, ColecaoJogadores, jogadores, pontos);
    //}

    winner = countPoints(pontos, jogadores);

    return 0;
}
