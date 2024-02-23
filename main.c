#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"
#include "pilha.h"
#include "fila.h"
#include "uni_game.h"

#define FILAS 4

int main()
{
    config();
    title();
    srand(time(NULL));

    Lista * Mao;
    Fila ** Mesa;
    Pilha * Baralho;
    Lista ** ColecaoJogadores;

    Mao = criar();
    Baralho = criarPilha();

    iniciarRound(Mao, Mesa, Baralho, ColecaoJogadores);

    return 0;
}
