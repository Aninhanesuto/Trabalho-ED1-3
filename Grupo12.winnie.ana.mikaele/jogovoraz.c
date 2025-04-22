#include "jogovoraz.h"

Direcao movimentos[4] = {{-1, 0, 'U'}, {1, 0, 'D'}, {0, -1, 'L'}, {0, 1, 'R'}};
// Funções da fila

//Função para inicializar os ponteiros da Fila.
void inicializaFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// Função para verificar se a fila está vazia.
booleano filaVazia(Fila *f) {
    return (f->inicio == NULL);
}

// Função para inserir na Fila.
void insereFila(Fila *f, int x, int y) {
    No *novo = (No *)malloc(sizeof(No));
    novo->x = x;
    novo->y = y;
    novo->prox = NULL;

    if (f->fim == NULL) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

//Função para excluir na fila e ajeitar os ponteiros inicio e fim.
No *excluiFila(Fila *f) {
    if (filaVazia(f)) return NULL;

    No *atual = f->inicio;
    f->inicio = atual->prox;

    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    return atual;
}

//Essa função verifica as posições válidas. 
/*  Resumo:
    Fora dos limites: Se a posição está fora da área do labirinto, é inválida.
    Paredes: Se a posição é uma parede ('#'), ela é bloqueada.
    Monstros: Monstros não podem entrar em células já invadidas por outros monstros.
    Tributo: O tributo não pode voltar para células já visitadas ('V') ou invadidas por monstros ('M').
*/

booleano posicaoValida(Labirinto *labirinto, int x, int y) {
    if (x < 0 || y < 0 || x >= labirinto->altura || y >= labirinto->largura) return false; // Fora dos limites
    if (labirinto->matriz[x][y] == '#') return false;  // Paredes são inválidas
    //Ela é considerada inválida para movimento, pois nem monstros nem o tributo podem passar por paredes.

    // Para o movimento dos monstros:
    if (labirinto->matriz[x][y] == 'M') return false;  // Monstros não podem entrar em células já invadidas por outros monstros

    // Para o movimento do tributo:
    if (labirinto->matriz[x][y] == 'V') return false;  // O tributo não pode entrar em células já visitadas
    if (labirinto->matriz[x][y] == 'M') return false;  // O tributo não pode entrar em células invadidas por monstros

    return true;  // Se passar por todas as verificações, a célula é válida
}




booleano isEscape(Labirinto *labirinto, int x, int y) {
    /*
    O objetivo dessa condição é verificar se a posição (x, y) está localizada em qualquer uma das bordas do labirinto.

    x == 0: Verifica se a posição está na borda superior do labirinto.
    y == 0: Verifica se a posição está na borda esquerda.
    x == labirinto->altura - 1: Verifica se a posição está na borda inferior.
    y == labirinto->largura - 1: Verifica se a posição está na borda direita.
    Mesmo que no início do jogo ele não esteja em uma borda (e isso já tenha sido verificado na main), ele vai andando conforme o algoritmo de busca em largura (BFS) é executado. Durante essa movimentação, a função isEscape é chamada para verificar se, em algum momento, ele alcança uma borda válida para escapar.
    Por que a verificação das bordas é importante?
    O objetivo do jogo é escapar do labirinto, e isso só pode acontecer se o tributo alcançar uma borda.
    À medida que o tributo se move no labirinto, o algoritmo precisa verificar constantemente se ele chegou a uma célula na borda que permita o escape.

    */
    // Verifica se está na borda!
    if ((x == 0 || y == 0 || x == labirinto->altura - 1 || y == labirinto->largura - 1)) {
        return true;
    }
    return false;
}


booleano buscaEmLargura(Labirinto *labirinto) {
    Fila fila;
    inicializaFila(&fila);

    // Matriz de direções para armazenar de onde o tributo veio
    char **direcoes = (char **)malloc(labirinto->altura * sizeof(char *));
    for (int i = 0; i < labirinto->altura; i++) {
        direcoes[i] = (char *)malloc(labirinto->largura * sizeof(char));
        for (int j = 0; j < labirinto->largura; j++) {
            direcoes[i][j] = '\0';  // Inicializa as direções como vazias
        }
    }

    // Insere todos os monstros na fila primeiro
    for (int i = 0; i < labirinto->altura; i++) {
        for (int j = 0; j < labirinto->largura; j++) {
            if (labirinto->matriz[i][j] == 'M') {
                insereFila(&fila, i, j);  // Adiciona monstros na fila
            }
        }
    }

    // Depois, insere o tributo
    insereFila(&fila, labirinto->tributoX, labirinto->tributoY);
    labirinto->matriz[labirinto->tributoX][labirinto->tributoY] = 'V';  // Marca como visitado pelo tributo

    while (!filaVazia(&fila)) {
        No *atual = excluiFila(&fila);
        int x = atual->x;
        int y = atual->y;
        free(atual);

        // Verifica se é um monstro
        if (labirinto->matriz[x][y] == 'M') {
            // Movimentação dos monstros
            for (int i = 0; i < 4; i++) {
                int novoX = x + movimentos[i].x;
                int novoY = y + movimentos[i].y;

                if (posicaoValida(labirinto, novoX, novoY)) {
                    labirinto->matriz[novoX][novoY] = 'M';  // Marca como invadido por monstros
                    insereFila(&fila, novoX, novoY);
                }
            }
        }
        // Caso seja o tributo
        else if (labirinto->matriz[x][y] == 'V') {
            // Movimentação do tributo
            for (int i = 0; i < 4; i++) {
                int novoX = x + movimentos[i].x;
                int novoY = y + movimentos[i].y;

                if (posicaoValida(labirinto, novoX, novoY)) {
                    direcoes[novoX][novoY] = movimentos[i].dir;  // Armazena a direção do movimento
                    labirinto->matriz[novoX][novoY] = 'V';  // Marca como visitado pelo tributo
                    insereFila(&fila, novoX, novoY);
                    
                    // Se encontrar a borda, reconstrua o caminho
                    if (isEscape(labirinto, novoX, novoY)) {
                        printf("YES\n");

                        // Reconstruir o caminho
                        char caminho[labirinto->altura * labirinto->largura];
                        int passos = 0;
                        int caminhoX = novoX, caminhoY = novoY;

                        while (!(caminhoX == labirinto->tributoX && caminhoY == labirinto->tributoY)) {
                            caminho[passos++] = direcoes[caminhoX][caminhoY];
                            switch (caminho[passos - 1]) {
                                case 'U':
                                    caminhoX++;
                                    break;
                                case 'D':
                                    caminhoX--;
                                    break;
                                case 'L':
                                    caminhoY++;
                                    break;
                                case 'R':
                                    caminhoY--;
                                    break;
                            }
                        }

                        // Imprime o comprimento do caminho e o caminho
                        printf("%d\n", passos);
                        for (int j = passos - 1; j >= 0; j--) {
                            printf("%c", caminho[j]);
                        }
                        printf("\n");
                        return true;
                    }
                }
            }
        }
    }

    // Se não for possível escapar
    printf("NO\n");
    return false;
}


