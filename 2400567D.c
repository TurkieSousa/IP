#include <stdio.h>

#define MAX_SEQ 100

// Funções para calcular o produto e a soma das sequência
int calcular_produto(int *sequencia, int tamanho) {
    int produto = 1;
    for (int i = 0; i < tamanho; i++) {
        produto *= sequencia[i];
    }
    return produto;
}

int calcular_soma(int *sequencia, int tamanho) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += sequencia[i];
    }
    return soma;
}

// Função para calcular o valor absoluto
int valor_absoluto(int x) {
    if (x < 0)
        return x * -1;
    else
        return x;
}

// Função para calcular a soma das diferenças absolutas
int calcular_diferencas_absolutas(int *sequencia, int tamanho) {
    int soma_diferencas = 0;
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            soma_diferencas += valor_absoluto(sequencia[i] - sequencia[j]);
        }
    }
    return soma_diferencas;
}

// Função para verificar a validade da sequência
int verificar_sequencia(int *sequencia, int tamanho, int k) {
    int produto = calcular_produto(sequencia, tamanho);
    int soma = calcular_soma(sequencia, tamanho);

    if (produto < k || soma > k) {
        return 0; // Sequência inválida
    }
    return 1; 
}

// Função para verificar se a sequência é de vitória
int verificar_sequencia_vitoria(int *sequencia, int tamanho, int k) {
    int diferencas_absolutas = calcular_diferencas_absolutas(sequencia, tamanho);
    if (diferencas_absolutas == k)
        return 1;
    else   
        return 0;
}

// Função para alternar o jogador
void alternar_jogador(char *jogador_atual, int *conta_jogadas) {
    // Alterna o jogador e reseta o contador de repetição de jogada
    if (*jogador_atual == 'A') {
        *jogador_atual = 'B';
    } else {
        *jogador_atual = 'A';
    }

    *conta_jogadas = 0;
}

// Função para verificar se o jogador pode repetir a jogada
int pode_repetir_jogada(int conta_jogadas) {
    if (conta_jogadas == 1)
        return 1;
    else   
        return 0;
}

// Função para selecionar o índice com maior valor na sequência
int selecionar_indice_maior_valor(int *sequencia, int tamanho) {
    int max_val = sequencia[0], indice = 0;
    for (int i = 1; i < tamanho; i++) {
        if (sequencia[i] > max_val) {
            max_val = sequencia[i];
            indice = i;
        }
    }
    return indice;
}

// Função para realizar a jogada artificial
void jogada_artificial(int *sequencia, int *tamanho, int k, int *indice, int *valor) {
    int i = selecionar_indice_maior_valor(sequencia, *tamanho);
    int v = sequencia[i];

    // Tentar reduzir, incrementar ou adicionar
    if (v > 1) {
        *indice = i;
        *valor = v - 1; // Reduz
    } else if (calcular_soma(sequencia, *tamanho) + 1 <= k) {
        *indice = *tamanho;
        *valor = 1; // Adiciona novo número
        sequencia[*tamanho] = 1;
        (*tamanho)++;
    } else {
        *indice = i;
        *valor = 0; // Remove
        for (int j = i; j < *tamanho - 1; j++) {
            sequencia[j] = sequencia[j + 1];
        }
        (*tamanho)--;
    }
}

int main() {
    int k, sequencia[MAX_SEQ], tamanho = 0, jogadas = 0, conta_jogadas = 0;
    char jogador_atual = 'A';

    // Entrada do valor de K
    printf("Indique K: ");
    scanf("%d", &k);

    // Configuração inicial da sequência
    sequencia[tamanho++] = k / 2;
    sequencia[tamanho++] = k / 2;

    while (jogadas < k) {
        int indice, valor;
        printf("\nSequencia: ");
        for (int i = 0; i < tamanho; i++) {
            printf("%d ", sequencia[i]);
        }
        printf("[Joga %c]\n", jogador_atual);

        printf("Jogada (indice valor): ");
        scanf("%d %d", &indice, &valor);

        // Jogada artificial
        if (indice == -2 && valor == -2) {
            jogada_artificial(sequencia, &tamanho, k, &indice, &valor);
            printf("Jogada artificial: %d %d\n", indice, valor);
        }

        // Efetuar a jogada
        if (indice >= tamanho) {
            if (valor != 0) {
                sequencia[tamanho++] = valor;
            }
        } else if (indice <= tamanho && valor == 0) {
            for (int i = indice; i < tamanho - 1; i++) {
                sequencia[i] = sequencia[i + 1];
            }
            tamanho--;
        } else if (valor < 0) {
            for (int i = tamanho; i > indice; i--) {
                sequencia[i] = sequencia[i - 1];
            }
            sequencia[indice] = -valor;
            tamanho++;
        } else {
            sequencia[indice] = valor;
        }

        // Verificar validade da sequência
        if (!verificar_sequencia(sequencia, tamanho, k)) {
            printf("\nSequencia: ");
            for (int i = 0; i < tamanho; i++) {
                printf("%d ", sequencia[i]);
            }
            printf("\nJogador %c perdeu.", jogador_atual);
            return 0;
        }

        // Verificar vitória
        if (verificar_sequencia_vitoria(sequencia, tamanho, k)) {
            printf("\nSequencia: ");
            for (int i = 0; i < tamanho; i++) {
                printf("%d ", sequencia[i]);
            }
            printf("\nJogador %c ganhou.", jogador_atual);
            return 0;
        }

        // Alternar jogador
        alternar_jogador(&jogador_atual, &conta_jogadas);
        jogadas++;
    }

    printf("\nSequencia: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", sequencia[i]);
    }
    printf("\nEmpate.");
}
