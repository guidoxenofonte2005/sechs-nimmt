#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "uni_game.h"
#include "lista.h"
#include "pilha.h"
#include "fila.h"

// aux/aesthetic functions

void color(int cor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cor);
}


// main/functions

void iniciarRound(Lista *mao, Fila ** mesa, Pilha * baralho, Lista ** ColecaoJogadores)
{

}
