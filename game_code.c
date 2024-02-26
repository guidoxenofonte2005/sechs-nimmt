#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <locale.h>
#include "uni_game.h"
#include "lista.h"
#include "pilha.h"
#include "fila.h"
#include "game_code.h"

#define CARDS 104
#define IND_CARDS 10
#define FILAS 4
#define ROUNDS 10
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
    SMALL_RECT windowSize = {0, 0, 89, 40};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);

}

void debugColor()
{
    for (int i = 0; i < 16; i++)
    {
        color(i);
        printf("[%d] - ", i);
    }
    color(15);
    printf("\n");
}

void title()
{
    color(14);
    printf("\404=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\404\n");
    color(4);
    printf("     _______ _______ _______ __   __ _______      __    _ ___ __   __ __   __ _______ \n");
    printf("    |       |       |       |  | |  |       |    |  |  | |   |  |_|  |  |_|  |       |\n");
    printf("    |  _____|    ___|       |  |_|  |  _____|    |   |_| |   |       |       |_     _|\n");
    printf("    | |_____|   |___|       |       | |_____     |       |   |       |       | |   |  \n");
    printf("    |_____  |    ___|      _|       |_____  |    |  _    |   |       |       | |   |  \n");
    printf("     _____| |   |___|     |_|   _   |_____| |    | | |   |   | ||_|| | ||_|| | |   |  \n");
    printf("    |_______|_______|_______|__| |__|_______|    |_|  |__|___|_|   |_|_|   |_| |___|  \n\n");
    color(9);
    printf("                                  /                       \\ \n");
    printf("                                /X/                       \\X\\ \n");
    printf("                               |XX\\         ____         /XX| \n");
    printf("                               |XXX\\     _/      \\_    /XXX| \n");
    printf("                                \\XXXXXXX            XXXXXXX/ \n");
    printf("                                  \\XXXX    \\    /    XXXXX/ \n");
    printf("                                       |   0    0   | \n");
    printf("                                        |          | \n");
    printf("                                        \\          / \n");
    printf("                                         \\        / \n");
    printf("                                          |,O__O,| \n");
    printf("                                          \\ ---- /  \n");
    printf("                                           \\ __ /\n");
    color(14);
    printf("\404=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\404\n");
    color(15);
}

void presentTurn(int turn)
{
    system("cls");
    printf("\n\n\n\n\n");
    printf("\t\t\t\t ROUND - %d", turn);
    Sleep(3000);
    system("cls");
}

// game functions

void inicializarBaralho(Pilha *baralho)
{
    Carta temp;
    while (!vaziaPilha(baralho))
    {
        int res = removerPilha(baralho, &temp);
    }

    Carta novaCarta;
    for (int i = 1; i <= CARDS; i++)
    {
        novaCarta.numero = i;
        novaCarta.jogador = 11; // no player
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

void realizarJogada(Lista *mao, Lista *cartasJogadas)
{
    int escolha, res;
    Carta temp;

    do
    {
        printf("Digite a carta: ");
        fflush(stdin);
        scanf("%d", &escolha);
    }
    while (escolha < 1 || escolha > 10);

    res = removerIndice(mao, escolha-1, &temp);
    res = inserirOrdenado(cartasJogadas, temp);
}

void jogadaCPU(Lista ** colecao, int jogadores, Lista *cartasJogadas)
{
    Carta temp;
    int res, choice;

    for (int i = 1; i < jogadores; i++) {
        temp.numero = NULL;
        temp.bois = NULL;
        temp.jogador = NULL;
        choice = rand() % quantidade(colecao[i]) + 1;
        res = removerIndice(colecao[i], choice-1, &temp);
        res = inserirOrdenado(cartasJogadas, temp);
    }
}

void selectPoints(Fila **mesa, int *pontuacao, Carta cartaInserida)
{
    Carta temp;
    int choice, res;
    do {
        printf("Digite a fila a ser removida e adicionada a seus pontos: ");
        fflush(stdin);
        scanf("%d", &choice);
    } while (choice < 1 || choice > FILAS);

    while (!vaziaFila(mesa[choice-1])) {
        res = removerFila(mesa[choice-1], &temp);
        pontuacao[0] += temp.bois;
    }
    res = inserirFila(mesa[choice-1], cartaInserida);
}

void cpuSelectPoints(Fila **mesa, int *pontuacao, int jogador, Carta cartaInserida)
{
    Carta temp;
    int random = rand() % FILAS;
    int res;

    res = removerFila(mesa[random], &temp);
    pontuacao[jogador] += temp.bois;
    res = inserirFila(mesa[random], cartaInserida);
}

void sortInsert(Fila **mesa, Lista *cartasJogadas, int *pontuacao)
{
    Carta temp, tempFila, placeholder;
    int change = 0, res, anterior, menor = 0;

    for (int i = 0; i < quantidade(cartasJogadas); i++) {
        res = acessarIndice(cartasJogadas, i, &temp);
        menor = 0;
        anterior = -1;
        for (int j = 0; j < FILAS; j++) {
            res = acessarFila(mesa[j], tamanhoFila(mesa[j])-1, &tempFila);
            if (tempFila.numero < temp.numero && (temp.numero - tempFila.numero) < (temp.numero - menor)) {
                anterior = j;
                menor = tempFila.numero;
            }
        }
        // printf("%d - %d, ", menor, anterior); // debug
        if (anterior == -1 && temp.jogador == 0) {
            selectPoints(mesa, pontuacao, temp);
        }
        else if (anterior == -1 && temp.jogador != 0) {
            cpuSelectPoints(mesa, pontuacao, temp.jogador, temp);
        }
        else if (tamanhoFila(mesa[anterior]) != 5){
            res = inserirFila(mesa[anterior], temp);
        }
        else {
            while (tamanhoFila(mesa[anterior]) != 0) {
                res = removerFila(mesa[anterior], &placeholder);
                pontuacao[temp.jogador] += placeholder.bois;
            }
            res = inserirFila(mesa[anterior], temp);
        }
        /*
        for (int k = 0; k < FILAS; k++) {
            res = exibirFila(mesa[k]);
        }
        Sleep(1000);
        //*/
    }
}

// main function
void RunGame(Lista *mao, Fila **mesa, Pilha *baralho, Lista **colecao, int jogadores, int *pontuacao)
{
    Carta temp, placeholder;
    Lista *played = NULL;
    int res;

    played = criar();

    inicializarBaralho(baralho);

    for (int i = 0; i < rand() % jogadores + 1; i++)
        embaralhar(baralho);

    // inicializar colecao
    colecao = (Lista **) malloc(jogadores * sizeof(Lista *));
    for (int i = 0; i < jogadores; i++)
    {
        colecao[i] = criar();
        for (int j = 0; j < IND_CARDS; j++)
        {
            res = removerPilha(baralho, &temp);
            temp.jogador = i;
            res = inserirOrdenado(colecao[i], temp);
        }
    }

    // inicializar mesa
    mesa = (Fila **) malloc(FILAS * sizeof(Fila *));
    for (int i = 0; i < FILAS; i++)
    {
        mesa[i] = criarFila();
        res = removerPilha(baralho, &temp);
        res = inserirFila(mesa[i], temp);
    }

    printf("\n");
    /* debug hands
    for (int i = 0; i < jogadores; i++) {
        res = exibirLista(colecao[i]);
        printf("\n");
    }
    //*/

    // mão do jogador
    mao = colecao[0];

    // colocar todo o código abaixo em um loop
    //for (int w = 0; w < ROUNDS; w++) {
        for (int i = 0; i < 4; i++)
        {
            res = exibirFila(mesa[i]);
        }
        printf("\n\n");

        for (int i = quantidade(played)-1; i >= 0; i--) {
            res = removerIndice(played, i, &placeholder);
        }

        res = exibirLista(played);

        res = exibirLista(mao);
        printf("\n\n");

        realizarJogada(mao, played);
        jogadaCPU(colecao, jogadores, played);

        printf("Cartas jogadas: ");
        exibirLista(played);
        Sleep(1200);
        printf("\n");

        sortInsert(mesa, played, pontuacao);

        for (int a = 0; a < jogadores; a++)
        {
            int num = pontuacao[a];
            printf("%d, ", num);
        }
        printf("\n\n");
    //}
}
/* CHECAR SE PRECISA MSM
int countPoints(int *pontos)
{

}
*/
