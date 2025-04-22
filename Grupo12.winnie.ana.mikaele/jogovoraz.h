#ifndef JOGOVORAZ_H
#define JOGOVORAZ_H

//Inclusão das bibliotecas necessárias.
#include <stdio.h>
#include <stdlib.h>

//definindo as macros, true como 1 e false como 0.
#define true 1
#define false 0

// definindo a macro do tipo int para booleano, só pra ser mais fácil
typedef int booleano;

//definindo a estrutura do labirinto.
typedef struct{
    int altura; //a altura(n) que o usuário irá digitar
    int largura; // a largura(m) que o usuário irá digitar.
    char **matriz; //Matriz que representa o labirinto.
    int tributoX, tributoY; //As posicoes do tributo.
}Labirinto;

//Definindo a estrutura para a fila usando lista ligada.
typedef struct auxNo{
    int x, y;
    struct auxNo* prox;
}No;
//Dois ponteiros para acessar o início e o final da fila para diminuir as contas.
typedef struct{
    No *inicio;
    No *fim;
}Fila;

// Struct das direcoes
typedef struct {
    int x, y;
    char dir;
} Direcao;

extern Direcao movimentos[4]; //usei o extern para essa chamada global não ir para os outros arquivos!
//Além disso, fiz um vetor da struct, para armazenar 4 posições!.

//Funcoes da Fila
void inicializaFila(Fila *f);
booleano filaVazia(Fila *f);
void insereFila(Fila* f, int x, int y);
No *excluiFila(Fila* f);

//Funcoes da Posição Valida, IsEscape, BFS.
booleano posicaoValida(Labirinto *labirinto, int x, int y);
booleano isEscape(Labirinto *labirinto, int x, int y);
booleano buscaEmLargura(Labirinto *labirinto);



#endif //JOGOVORAZ_H
