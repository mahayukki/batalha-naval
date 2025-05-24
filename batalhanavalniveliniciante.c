#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

// Função para verificar se o navio cabe dentro do tabuleiro
int verifica_limite(int linha, int coluna, char orientacao) {
    if (orientacao == 'H') {
        return coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO;
    } else if (orientacao == 'V') {
        return linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO;
    }
    return 0;
}

// Função para verificar se há sobreposição de navios
int verifica_sobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (orientacao == 'H') {
            if (tabuleiro[linha][coluna + i] == VALOR_NAVIO)
                return 1; // Há sobreposição
        } else if (orientacao == 'V') {
            if (tabuleiro[linha + i][coluna] == VALOR_NAVIO)
                return 1;
        }
    }
    return 0; // Sem sobreposição
}

// Função para posicionar o navio no tabuleiro
void posiciona_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (orientacao == 'H') {
            tabuleiro[linha][coluna + i] = VALOR_NAVIO;
        } else if (orientacao == 'V') {
            tabuleiro[linha + i][coluna] = VALOR_NAVIO;
        }
    }
}

// Função para exibir o tabuleiro
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
    // Inicializa o tabuleiro com água (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Coordenadas e orientações dos navios (pré-definidas)
    int linha1 = 2, coluna1 = 3; // Navio 1 - horizontal
    int linha2 = 5, coluna2 = 7; // Navio 2 - vertical
    char orientacao1 = 'H';
    char orientacao2 = 'V';

    // Validações para navio 1
    if (verifica_limite(linha1, coluna1, orientacao1) && 
        !verifica_sobreposicao(tabuleiro, linha1, coluna1, orientacao1)) {
        posiciona_navio(tabuleiro, linha1, coluna1, orientacao1);
    } else {
        printf("Erro ao posicionar o navio 1.\n");
    }

    // Validações para navio 2
    if (verifica_limite(linha2, coluna2, orientacao2) &&
        !verifica_sobreposicao(tabuleiro, linha2, coluna2, orientacao2)) {
        posiciona_navio(tabuleiro, linha2, coluna2, orientacao2);
    } else {
        printf("Erro ao posicionar o navio 2.\n");
    }

    // Exibe o tabuleiro final
    exibe_tabuleiro(tabuleiro);

    return 0;
}