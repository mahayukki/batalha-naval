#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define TAM_NAVIO 3
#define TAM_HAB 5 // Tamanho fixo das matrizes de habilidades
#define VALOR_AGUA 0
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5

// Verifica limites de inserção de navio
int dentro_dos_limites(int linha, int coluna, char orientacao) {
    switch (orientacao) {
        case 'H': return coluna + TAM_NAVIO <= TAM;
        case 'V': return linha + TAM_NAVIO <= TAM;
        case 'D': return linha + TAM_NAVIO <= TAM && coluna + TAM_NAVIO <= TAM;
        case 'A': return linha + TAM_NAVIO <= TAM && coluna - TAM_NAVIO + 1 >= 0;
        default: return 0;
    }
}

// Verifica se há sobreposição
int ha_sobreposicao(int tabuleiro[TAM][TAM], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;
        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'D') { l += i; c += i; }
        else if (orientacao == 'A') { l += i; c -= i; }

        if (tabuleiro[l][c] == VALOR_NAVIO) return 1;
    }
    return 0;
}

// Posiciona navio
void posiciona_navio(int tabuleiro[TAM][TAM], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;
        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'D') { l += i; c += i; }
        else if (orientacao == 'A') { l += i; c -= i; }
        tabuleiro[l][c] = VALOR_NAVIO;
    }
}

// Gera matriz cone (parte superior = origem)
void gera_matriz_cone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= TAM_HAB/2 - i && j <= TAM_HAB/2 + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera matriz cruz (centro = origem)
void gera_matriz_cruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB/2 || j == TAM_HAB/2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera matriz octaedro (losango em volta do centro)
void gera_matriz_octaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB/2) + abs(j - TAM_HAB/2) <= TAM_HAB/2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica matriz de habilidade ao tabuleiro
void aplica_habilidade(int tabuleiro[TAM][TAM], int matriz[TAM_HAB][TAM_HAB], int origem_linha, int origem_coluna) {
    int offset = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int l = origem_linha - offset + i;
            int c = origem_coluna - offset + j;

            if (l >= 0 && l < TAM && c >= 0 && c < TAM) {
                if (matriz[i][j] == 1 && tabuleiro[l][c] != VALOR_NAVIO)
                    tabuleiro[l][c] = VALOR_HABILIDADE;
            }
        }
    }
}

// Imprime o tabuleiro com legenda
void imprime_tabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nLegenda: 0=Água, 3=Navio, 5=Área de Habilidade\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0};

    // Dados dos navios: linha, coluna, orientação
    int navios[4][3] = {
        {1, 1, 'H'}, // Horizontal
        {3, 4, 'V'}, // Vertical
        {0, 0, 'D'}, // Diagonal descendo
        {5, 9, 'A'}  // Diagonal ascendente
    };

    // Posiciona navios
    for (int i = 0; i < 4; i++) {
        int l = navios[i][0], c = navios[i][1];
        char o = navios[i][2];
        if (dentro_dos_limites(l, c, o) && !ha_sobreposicao(tabuleiro, l, c, o))
            posiciona_navio(tabuleiro, l, c, o);
        else
            printf("Erro ao posicionar navio %d\n", i + 1);
    }

    // Matrizes de habilidades
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octa[TAM_HAB][TAM_HAB];

    gera_matriz_cone(cone);
    gera_matriz_cruz(cruz);
    gera_matriz_octaedro(octa);

    // Pontos de origem das habilidades no tabuleiro
    aplica_habilidade(tabuleiro, cone, 2, 2);
    aplica_habilidade(tabuleiro, cruz, 5, 5);
    aplica_habilidade(tabuleiro, octa, 7, 7);

    // Exibe o resultado
    imprime_tabuleiro(tabuleiro);

    return 0;
}