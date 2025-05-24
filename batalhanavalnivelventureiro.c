#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

// Função para verificar se o navio está dentro dos limites (horizontal, vertical ou diagonal)
int verifica_limite(int linha, int coluna, char orientacao) {
    switch (orientacao) {
        case 'H': return coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO;
        case 'V': return linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO;
        case 'D': return linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO;
        case 'A': return linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && coluna - TAMANHO_NAVIO + 1 >= 0;
        default: return 0;
    }
}

// Verifica sobreposição para qualquer orientação
int verifica_sobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;

        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'D') { l += i; c += i; }
        else if (orientacao == 'A') { l += i; c -= i; }

        if (tabuleiro[l][c] == VALOR_NAVIO) return 1;
    }
    return 0;
}

// Posiciona o navio na matriz
void posiciona_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;

        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'D') { l += i; c += i; }
        else if (orientacao == 'A') { l += i; c -= i; }

        tabuleiro[l][c] = VALOR_NAVIO;
    }
}

// Exibe o tabuleiro no console
void exibe_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro Batalha Naval:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Inicializa o tabuleiro com água
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Dados dos 4 navios: {linha, coluna, orientação}
    // Orientações: H - horizontal, V - vertical, D - diagonal descendo (linha++, col++), A - diagonal ascendente (linha++, col--)
    int navios[4][3] = {
        {1, 2, 'H'},  // navio 1 horizontal
        {4, 5, 'V'},  // navio 2 vertical
        {0, 0, 'D'},  // navio 3 diagonal descendo
        {2, 8, 'A'}   // navio 4 diagonal ascendente
    };

    // Posiciona os 4 navios com validação
    for (int i = 0; i < 4; i++) {
        int linha = navios[i][0];
        int coluna = navios[i][1];
        char orientacao = (char)navios[i][2];

        if (verifica_limite(linha, coluna, orientacao) &&
            !verifica_sobreposicao(tabuleiro, linha, coluna, orientacao)) {
            posiciona_navio(tabuleiro, linha, coluna, orientacao);
        } else {
            printf("Erro ao posicionar o navio %d.\n", i + 1);
        }
    }

    // Exibe o tabuleiro final
    exibe_tabuleiro(tabuleiro);

    return 0;
}