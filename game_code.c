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

#define MIN_SIZE 32

#define STYLE_LD_DOTS 3

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
    SMALL_RECT windowSize = {0, 0, 89, 45};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
}

void debugColor()
{
    for (int i = 1; i < 16; i++)
    {
        color(i);
        printf("[%d] - ", i);
    }
    color(15);
    printf("\n");
}

void title()
{
    color(8);
    printf("\404=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\404\n");
    Sleep(800);
    color(4);
    printf("     _______ _______ _______ __   __ _______      __    _ ___ __   __ __   __ _______ \n");
    printf("    |       |       |       |  | |  |       |    |  |  | |   |  |_|  |  |_|  |       |\n");
    printf("    |  _____|    ___|       |  |_|  |  _____|    |   |_| |   |       |       |_     _|\n");
    printf("    | |_____|   |___|       |       | |_____     |       |   |       |       | |   |  \n");
    printf("    |_____  |    ___|      _|       |_____  |    |  _    |   |       |       | |   |  \n");
    printf("     _____| |   |___|     |_|   _   |_____| |    | | |   |   | ||_|| | ||_|| | |   |  \n");
    printf("    |_______|_______|_______|__| |__|_______|    |_|  |__|___|_|   |_|_|   |_| |___|  \n\n");
    Sleep(800);
    color(9);
    printf("                                 /                       \\ \n");
    printf("                               /X/                       \\X\\ \n");
    printf("                              |XX\\         ____         /XX| \n");
    printf("                              |XXX\\     _/      \\_    /XXX| \n");
    printf("                               \\XXXXXXX            XXXXXXX/ \n");
    printf("                                 \\XXXX    \\    /    XXXXX/ \n");
    printf("                                      |   0    0   | \n");
    printf("                                       |          | \n");
    printf("                                       \\          / \n");
    printf("                                        \\        / \n");
    printf("                                         |,O__O,| \n");
    printf("                                         \\ ---- /  \n");
    printf("                                          \\ __ /\n");
    color(8);
    Sleep(800);
    printf("\404=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\404\n");
    Sleep(800);
    color(15);
}

void presentTurn(int turn)
{
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    color(4);
    printf("\t\t\t\t\t ROUND - %d", turn);
    color(15);
    Sleep(3000);
    system("cls");
}

void loadingScreen()
{
    int time = rand() % 4 + 1;
    for (int i = 0; i < time; i++)
    {
        int interval = rand() % 400 + 1;
        system("cls");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        color(8);
        printf("\t\t\t\t\t Loading");
        for (int j = 0; j < STYLE_LD_DOTS; j++)
        {
            Sleep(interval);
            printf(".");
            Sleep(100);
        }
    }
}

void showPoints(int * pontuacao, int jogadores)
{
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    color(12);
    printf("\t\t\t\t\t Pontuação:\n");
    color(8);
    printf("\t\t\t\t\t - Você - %d -\n", pontuacao[0]);
    for (int i = 1; i < jogadores; i++)
        printf("\t\t\t\t\t - CPU%d - %d -\n", i, pontuacao[i]);
    color(15);
    Sleep(3000);
    system("cls");
}

int titleOptions()
{
    int opt;

    printf("\n\n\t\t\t\t 1. Jogar\n");
    Sleep(500);
    printf("\t\t\t\t 2. Regras\n");
    Sleep(500);
    printf("\t\t\t\t 3. Opções\n");
    Sleep(400);
    do {
        printf("\t\t\t\t Digite sua escolha: ");
        fflush(stdin);
        scanf("%d", &opt);
    } while (opt < 1 || opt > 3);

    switch (opt)
    {
    case 1:
        return 1;
        break;
    case 2:
        rules();
        break;
    case 3:
        options();
        break;
    }

    return 0;
}

void rules()
{
    system("cls");
    color(8);
    printf("\404=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\404\n");
    color(4);
    printf("                    ______  ______  ______  ______  ______  ______\n");
    printf("                   /\\  == \\/\\  ___\\/\\  ___\\/\\  == \\/\\  __ \\/\\  ___\\\n");
    printf("                   \\ \\  __<\\ \\  __\\\\ \\ \\__ \\ \\  __<\\ \\  __ \\ \\___  \\\n");
    printf("                    \\ \\_\\ \\_\\ \\_____\\ \\_____\\ \\_\\ \\_\\ \\_\\ \\_\\/\\_____\\\n");
    printf("                     \\/_/ /_/\\/_____/\\/_____/\\/_/ /_/\\/_/\\/_/\\/_____/\n\n");
    color(8);
    printf("\404=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\404\n");

    printf("\t\tOBJETIVO DO JOGO \t      ||\t     EXEMPLO DE CARTA\n\t\t\t\t\t      ||\n");
    printf("    O objetivo do jogo é pegar cartas. Cada   ||\t.--=-=--.\n");
    printf(" carta que você pega lhe rende um ponto nega- ||\t|%% %% %% %%|\n");
    printf(" tivo para cada cabeça de boi impressa sobre  ||\t| %% %% %% |\n");
    printf(" a carta. O jogador com menos pontos após al- ||\t|   55--|-> N° da carta\n");
    printf(" gumas rodadas é o vencedor.                  ||\t| %% %% %% |\n");
    printf("                                              ||\t|%% %% %% %%|--> Bois/pontuação\n");
    printf("                                              ||\t\'--=-=--\'\n");
    printf("\404=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\404\n");
    printf("\t\t   COMO JOGAR \t\t      ||\t     PEGANDO UMA FILA\n");
    printf("    Cada jogador escolhe uma carta de sua mão ||   Para pegar uma fila para ser adiciona-\n");
    printf(" e coloca-a virada para baixo sobre a mesa. Ao||da aos pontos do jogador, o jogador deve:\n");
    printf(" fim da escolha de todos, os jogadores revelam||  1-Escolher uma carta menor que todas as\n");
    printf(" as cartas e colocam-nas nas respectivas filas||cartas já existentes na mesa;\n");
    printf(" em ordem crescente. Caso a carta seja maior  ||  2-Inserir em uma das filas uma carta de\n");
    printf(" que duas ou mais filas, ela será colocada na ||modo que a fila possua seis cartas.\n");
    printf(" fila cujo número da última carta está mais   ||   Caso uma das condições acima seja sa-\n");
    printf(" próximo da carta a ser inserida.             ||tisfeita, todas as cartas removidas serão\n");
    printf("                                              ||adicionadas aos pontos do jogador e a úl-\n");
    printf("                                              ||tima carta ficará no lugar das outras.\n");
    printf("\404=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\404\n\n");
    printf("\t\t\t\tDigite ENTER para voltar: ");
    fflush(stdin);
    getchar();
    system("cls");
}

void options()
{
    system("cls");
    color(8);
    printf("\404=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\404\n");
    color(4);
    printf("                      ______  ______  ______  ______  ______  ______\n");
    printf("                     /\\  __ \\/\\  == \\/\\  ___\\/\\  __ \\/\\  ___\\/\\  ___\\\n");
    printf("                     \\ \\ \\/\\ \\ \\  _-/\\ \\ \\___\\ \\ \\/\\ \\ \\  __\\\\ \\___  \\\n");
    printf("                      \\ \\_____\\ \\_\\   \\ \\_____\\ \\_____\\ \\_____\\/\\_____\\\n");
    printf("                       \\/_____/\\/_/    \\/_____/\\/_____/\\/_____/\\/_____/\n\n");
    color(8);
    printf("\404=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\404\n");
    printf("   _    _ _           _                     ||   _    _ _           _                      \n");
    printf("  | |  | (_)         | |                    ||  | |  | (_)         | |                     \n");
    printf("  | |  | |_ _ __   __| | _____      _____   ||  | |  | |_ _ __   __| | _____      _____    \n");
    printf("  | |/\\| | | '_ \\ / _` |/ _ \\ \\ /\\ / / __|  ||  | |/\\| | | '_ \\ / _` |/ _ \\ \\ /\\ / / __|   \n");
    printf("  \\  /\\  | | | | | (_| | (_) \\ V  V /\\__ \\  ||  \\  /\\  | | | | | (_| | (_) \\ V  V /\\__ \\   \n");
    printf("   \\/  \\/|_|_| |_|\\__,_|\\___/ \\_/\\_/ |___/  ||   \\/  \\/|_|_| |_|\\__,_|\\___/ \\_/\\_/ |___/   \n");
    printf("                 __  _____                  ||                 __  __  \n");
    printf("                /  ||  _  |                 ||                /  |/  | \n");
    printf("                `| || |/' |                 ||                `| |`| | \n");
    printf("                _| |\\ |_/ /                 ||                _| |_| |_\n");
    printf("                \\___/\\___/                  ||                \\___\\___/\n");
    printf("                                            ||\n");
    printf("   Todas as configurações para o SO já fo-  ||   1 - Digite \'cmd\' na barra de pesquisas;\n");
    printf("  ram realizadas pelo código. Aproveite!    ||   2 - Clique na seta presente ao lado do\n");
    printf("                                            ||  título do console e entre nas Configura-\n");
    printf("          _     _                           ||  ções;\n");
    printf("         | |   (_)                          ||   3 - Desça até a área \'Tamanho de inici-\n");
    printf("         | |    _ _ __  _   ___  __         ||  alização\' e ajuste as dimensões para 90\n");
    printf("         | |   | | '_ \\| | | \\ \\/ /         ||  colunas e 45 linhas;\n");
    printf("         | |___| | | | | |_| |>  <          ||   4 - Na coluna lateral, na área \'Perfis\',\n");
    printf("         \\_____|_|_| |_|\\__,_/_/\\_\\         ||  acesse o perfil \'Padrões\' e entre na á-\n");
    printf("                                            ||  rea \'Aparência\';\n");
    printf("   Delete o sistema operacional e realize   ||   5 - Altere o tamanho da fonte para 9;\n");
    printf("  a instalação do Windows 10/11...          ||   6 - Aproveite!\n");
    printf("\404=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\404\n");
    color(15);
    printf("\t\t\t\tDigite ENTER para voltar: ");
    fflush(stdin);
    getchar();
    system("cls");
}

void credits()
{
    Sleep(500);
    color(4);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t     ______  __  __     ______  ______  __    __  ______  ______\n");
    printf("\t    /\\  ___\\/\\_\\_\\_\\   /\\  ___\\/\\  __ \\/\\ \"-./  \\/\\  ___\\/\\  ___\\\n");
    printf("\t    \\ \\ \\__ \\/_/\\_\\/_  \\ \\ \\__ \\ \\  __ \\ \\ \\-./\\ \\ \\  __\\\\ \\___  \\\n");
    printf("\t     \\ \\_____\\/\\_\\|\\_\\  \\ \\_____\\ \\_\\ \\_\\ \\_\\ \\ \\_\\ \\_____\\/\\_____\\\n");
    printf("\t      \\/_____/\\/_/\\/_/   \\/_____/\\/_/\\/_/\\/_/  \\/_/\\/_____/\\/_____/\n\n");
    printf("\t     ______  ______  ______  ______  ______  __   __  ______  ______\n");
    printf("\t    /\\  == \\/\\  == \\/\\  ___\\/\\  ___\\/\\  ___\\/\\ \"-.\\ \\/\\__  _\\/\\  ___\\\n");
    printf("\t    \\ \\  _-/\\ \\  __<\\ \\  __\\\\ \\___  \\ \\  __\\\\ \\ \\-.  \\/_/\\ \\/\\ \\___  \\\n");
    printf("\t     \\ \\_\\   \\ \\_\\ \\_\\ \\_____\\/\\_____\\ \\_____\\ \\_\\\\\"\\_\\ \\ \\_\\ \\/\\_____\\\n");
    printf("\t      \\/_/    \\/_/ /_/\\/_____/\\/_____/\\/_____/\\/_/ \\/_/  \\/_/  \\/_____/\n");
    Sleep(2500);
    system("cls");
    color(12);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t     ______  __  __     ______  ______  __    __  ______  ______\n");
    printf("\t    /\\  ___\\/\\_\\_\\_\\   /\\  ___\\/\\  __ \\/\\ \"-./  \\/\\  ___\\/\\  ___\\\n");
    printf("\t    \\ \\ \\__ \\/_/\\_\\/_  \\ \\ \\__ \\ \\  __ \\ \\ \\-./\\ \\ \\  __\\\\ \\___  \\\n");
    printf("\t     \\ \\_____\\/\\_\\|\\_\\  \\ \\_____\\ \\_\\ \\_\\ \\_\\ \\ \\_\\ \\_____\\/\\_____\\\n");
    printf("\t      \\/_____/\\/_/\\/_/   \\/_____/\\/_/\\/_/\\/_/  \\/_/\\/_____/\\/_____/\n\n");
    printf("\t     ______  ______  ______  ______  ______  __   __  ______  ______\n");
    printf("\t    /\\  == \\/\\  == \\/\\  ___\\/\\  ___\\/\\  ___\\/\\ \"-.\\ \\/\\__  _\\/\\  ___\\\n");
    printf("\t    \\ \\  _-/\\ \\  __<\\ \\  __\\\\ \\___  \\ \\  __\\\\ \\ \\-.  \\/_/\\ \\/\\ \\___  \\\n");
    printf("\t     \\ \\_\\   \\ \\_\\ \\_\\ \\_____\\/\\_____\\ \\_____\\ \\_\\\\\"\\_\\ \\ \\_\\ \\/\\_____\\\n");
    printf("\t      \\/_/    \\/_/ /_/\\/_____/\\/_____/\\/_____/\\/_/ \\/_/  \\/_/  \\/_____/\n");
    Sleep(100);
    system("cls");
    color(15);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t     ______  __  __     ______  ______  __    __  ______  ______\n");
    printf("\t    /\\  ___\\/\\_\\_\\_\\   /\\  ___\\/\\  __ \\/\\ \"-./  \\/\\  ___\\/\\  ___\\\n");
    printf("\t    \\ \\ \\__ \\/_/\\_\\/_  \\ \\ \\__ \\ \\  __ \\ \\ \\-./\\ \\ \\  __\\\\ \\___  \\\n");
    printf("\t     \\ \\_____\\/\\_\\|\\_\\  \\ \\_____\\ \\_\\ \\_\\ \\_\\ \\ \\_\\ \\_____\\/\\_____\\\n");
    printf("\t      \\/_____/\\/_/\\/_/   \\/_____/\\/_/\\/_/\\/_/  \\/_/\\/_____/\\/_____/\n\n");
    printf("\t     ______  ______  ______  ______  ______  __   __  ______  ______\n");
    printf("\t    /\\  == \\/\\  == \\/\\  ___\\/\\  ___\\/\\  ___\\/\\ \"-.\\ \\/\\__  _\\/\\  ___\\\n");
    printf("\t    \\ \\  _-/\\ \\  __<\\ \\  __\\\\ \\___  \\ \\  __\\\\ \\ \\-.  \\/_/\\ \\/\\ \\___  \\\n");
    printf("\t     \\ \\_\\   \\ \\_\\ \\_\\ \\_____\\/\\_____\\ \\_____\\ \\_\\\\\"\\_\\ \\ \\_\\ \\/\\_____\\\n");
    printf("\t      \\/_/    \\/_/ /_/\\/_____/\\/_____/\\/_____/\\/_/ \\/_/  \\/_/  \\/_____/\n");
    Sleep(100);
    system("cls");
    color(8);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t     ______  __  __     ______  ______  __    __  ______  ______\n");
    printf("\t    /\\  ___\\/\\_\\_\\_\\   /\\  ___\\/\\  __ \\/\\ \"-./  \\/\\  ___\\/\\  ___\\\n");
    printf("\t    \\ \\ \\__ \\/_/\\_\\/_  \\ \\ \\__ \\ \\  __ \\ \\ \\-./\\ \\ \\  __\\\\ \\___  \\\n");
    printf("\t     \\ \\_____\\/\\_\\|\\_\\  \\ \\_____\\ \\_\\ \\_\\ \\_\\ \\ \\_\\ \\_____\\/\\_____\\\n");
    printf("\t      \\/_____/\\/_/\\/_/   \\/_____/\\/_/\\/_/\\/_/  \\/_/\\/_____/\\/_____/\n\n");
    printf("\t     ______  ______  ______  ______  ______  __   __  ______  ______\n");
    printf("\t    /\\  == \\/\\  == \\/\\  ___\\/\\  ___\\/\\  ___\\/\\ \"-.\\ \\/\\__  _\\/\\  ___\\\n");
    printf("\t    \\ \\  _-/\\ \\  __<\\ \\  __\\\\ \\___  \\ \\  __\\\\ \\ \\-.  \\/_/\\ \\/\\ \\___  \\\n");
    printf("\t     \\ \\_\\   \\ \\_\\ \\_\\ \\_____\\/\\_____\\ \\_____\\ \\_\\\\\"\\_\\ \\ \\_\\ \\/\\_____\\\n");
    printf("\t      \\/_/    \\/_/ /_/\\/_____/\\/_____/\\/_____/\\/_/ \\/_/  \\/_/  \\/_____/\n");
    Sleep(100);
    system("cls");
    Sleep(200);
}

void revealCards(int jogadores, Lista *played)
{
    int espacos;
    espacos = ((10 - jogadores) * 4);

    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t    CARTAS JOGADAS:\n");
    Sleep(500);
    for (int i = 0; i < espacos; i++)
        printf(" ");

    for (int i = 0; i < jogadores; i++)
        printf(".--=-=--.");

    printf("\n");
    for (int i = 0; i < espacos; i++)
        printf(" ");

    for (int i = 0; i < jogadores; i++)
        printf("|\\     /|");

    printf("\n");
    for (int i = 0; i < espacos; i++)
        printf(" ");

    for (int i = 0; i < jogadores; i++)
        printf("|\\\\~~~//|");

    printf("\n");
    for (int i = 0; i < espacos; i++)
        printf(" ");

    for (int i = 0; i < jogadores; i++)
        printf("|\'\\o o/\'|");

    printf("\n");
    for (int i = 0; i < espacos; i++)
        printf(" ");

    for (int i = 0; i < jogadores; i++)
        printf("| (._.) |");

    printf("\n");
    for (int i = 0; i < espacos; i++)
        printf(" ");

    for (int i = 0; i < jogadores; i++)
        printf("|  \\_/  |");

    printf("\n");
    for (int i = 0; i < espacos; i++)
        printf(" ");

    for (int i = 0; i < jogadores; i++)
        printf("\'--=-=--\'");

    Sleep(1200);
    system("cls");

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t    CARTAS JOGADAS:\n");
    int res = exibirLista(played);

    Sleep(1500);
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
        fflush(stdin);
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

    while (!vaziaFila(mesa[random])) {
        res = removerFila(mesa[random], &temp);
        pontuacao[jogador] += temp.bois;
    }
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
    for (int w = 0; w < ROUNDS; w++) {
        system("cls");
        for (int i = 0; i < 4; i++)
        {
            res = exibirFila(mesa[i]);
        }
        printf("\n");

        for (int i = quantidade(played)-1; i >= 0; i--) {
            res = removerIndice(played, i, &placeholder);
        }

        res = exibirLista(played);

        printf("\t\t\t\t         SUA MÃO:\n");
        res = exibirLista(mao);

        realizarJogada(mao, played);
        jogadaCPU(colecao, jogadores, played);

        Sleep(500);

        revealCards(jogadores, played);

        Sleep(1200);
        printf("\n");

        sortInsert(mesa, played, pontuacao);

        printf("\n\n");
    }
}

// ending functions
int countPoints(int *pontuacao, int jogadores)
{
    int menor;
    for (int i = 0; i < jogadores; i++)
    {
        if (i == 0)
            menor = 0;
        else if (pontuacao[i] < pontuacao[menor])
            menor = i;
    }
    return menor;
}
