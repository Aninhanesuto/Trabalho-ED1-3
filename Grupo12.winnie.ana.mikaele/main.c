#include "jogovoraz.h"

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Labirinto labirinto;
    labirinto.altura = n;
    labirinto.largura = m;
    labirinto.matriz = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        labirinto.matriz[i] = (char *)malloc(m * sizeof(char));
    }
    

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            scanf(" %c", &c);
            labirinto.matriz[i][j] = c;
            //Definição da posição inicial do Tributo.
            if (c == 'A') {
                labirinto.tributoX = i;
                labirinto.tributoY = j;
            }
        }
    }

    // Verifica se já é possível escapar de imediato
    /* Essa função verifica se o tributo está em uma das bordas, se ele estiver, 
    já é possível ele escapar e imprime 0. Portanto, não é preciso fazer a BFS ou propagar os monstros, 
    porque ele já pode escapar.
    */
    if (labirinto.tributoX == 0 || labirinto.tributoY == 0 || 
        labirinto.tributoX == n - 1 || labirinto.tributoY == m - 1) {
        printf("YES\n0\n");
        return 0;  
    }

    // A propagação dos monstros do tributo e a BFS começa aqui
    buscaEmLargura(&labirinto);

    // Liberação da memória.
    for (int i = 0; i < n; i++) {
        free(labirinto.matriz[i]);
    }
    free(labirinto.matriz);

    return 0;
}
