#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include "uni_game.h"
#include "lista.h"
#include "pilha.h"
#include "fila.h"

#define CARDS 104
#define IND_CARDS 10
#define FILAS 4
// aux/aesthetic functions

void color(int cor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cor);
}

void config()
{
    setlocale(LC_ALL, "Portuguese");

    // CONSOLE CONFIG
    HWND consoleWindow = GetConsoleWindow();

    SetWindowPos(consoleWindow, 0, 550, 160, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, 89, 30};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);

}

void title()
{
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("     _______ _______ _______ __   __ _______      __    _ ___ __   __ __   __ _______ \n");
    printf("    |       |       |       |  | |  |       |    |  |  | |   |  |_|  |  |_|  |       |\n");
    printf("    |  _____|    ___|       |  |_|  |  _____|    |   |_| |   |       |       |_     _|\n");
    printf("    | |_____|   |___|       |       | |_____     |       |   |       |       | |   |  \n");
    printf("    |_____  |    ___|      _|       |_____  |    |  _    |   |       |       | |   |  \n");
    printf("     _____| |   |___|     |_|   _   |_____| |    | | |   |   | ||_|| | ||_|| | |   |  \n");
    printf("    |_______|_______|_______|__| |__|_______|    |_|  |__|___|_|   |_|_|   |_| |___|  \n\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("                               /                       \\ \n");
    printf("                             /X/                       \\X\\ \n");
    printf("                            |XX\\         _____         /XX| \n");
    printf("                            |XXX\\     _/       \\_    /XXX| \n");
    printf("                             \\XXXXXXX             XXXXXXX/ \n");
    printf("                               \\XXXX    \\     /    XXXXX/ \n");
    printf("                                    |   0     0   | \n");
    printf("                                     |           | \n");
    printf("                                      \\         / \n");
    printf("                                       \\       / \n");
    printf("                                        |,O_O,| \n");
    printf("                                         \\ _ /  \n");
}

// main functions

void inicializarBaralho(Pilha *baralho)
{
    Carta temp;
    while (!vaziaPilha(baralho)) {
        int res = removerPilha(baralho, &temp);
    }

    Carta novaCarta;
    for (int i = 1; i <= CARDS; i++) {
        novaCarta.numero = i;
        int bois = 0;
        if (novaCarta.numero % 5 == 0 && novaCarta.numero % 10 != 0)
            bois += 2;
        if (novaCarta.numero % 10 == 0)
            bois += 3;
        if (novaCarta.numero % 11 == 0)
            bois += 5;
        if (bois == 0)
            bois += 1;
        novaCarta.bois = bois;

        int res = inserirPilha(baralho, novaCarta);
    }
}

void iniciarRound(Lista *mao, Fila **mesa, Pilha *baralho, Lista **colecao, int jogadores)
{
    Carta temp;
    int res;

    inicializarBaralho(baralho);

    embaralhar(baralho);

    // inicializar colecao
    colecao = (Lista **) malloc(jogadores * sizeof(Lista *));
    for (int i = 0; i < jogadores; i++) {
        colecao[i] = criar();
        for (int j = 0; j < IND_CARDS; j++) {
            res = removerPilha(baralho, &temp);
            temp.jogador = i;
            res = inserirOrdenado(colecao[i], temp);
        }
        printf("\n");
        res = exibirLista(colecao[i]);
    }

    // inicializar mesa
    mesa = (Fila **) malloc(FILAS * sizeof(Fila *));
    for (int i = 0; i < FILAS; i++) {
        mesa[i] = criarFila();
        res = removerPilha(baralho, &temp);
        temp.jogador = 11; // no player
        res = inserirFila(mesa[i], temp);
    }

    // mão do jogador
    *mao = colecao[0];

    for (int i = 0; i < 4; i++)
        res = exibirFila(mesa[i]);

}
