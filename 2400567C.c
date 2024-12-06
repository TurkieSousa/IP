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
    return 1; // Sequência válida
}

// Função para verificar se a sequência é de vitória
int verificar_sequencia_vitoria(int *sequencia, int tamanho, int k) {
    int diferencas_absolutas = calcular_diferencas_absolutas(sequencia, tamanho);
    return (diferencas_absolutas == k);
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
    return conta_jogadas == 1;  // O jogador pode repetir a jogada se já fez 1 jogada previamente
}

int main() {
    int k, sequencia[MAX_SEQ], tamanho = 0, num, jogadas = 0, conta_jogadas = 0;
    char jogador_atual = 'A';

    // Entrada dos valores de K e sequência
    printf("Indique K: ");
    scanf("%d", &k);

    num = k / 2;

    do {
        sequencia[tamanho] = num;
        tamanho++;
    } while (tamanho < 2);

    while (jogadas < k) {
        int indice, valor;
        printf("\nSequencia: ");
        for (int i = 0; i < tamanho; i++) {
            printf("%d ", sequencia[i]);
        }
        printf("[Joga %c]\n", jogador_atual);

        printf("Jogada (indice valor): ");
        scanf("%d %d", &indice, &valor);
		
		if (indice < 0 )
			indice = 0;

        // Efetuar a jogada
        if (indice >= tamanho) {
            if (valor != 0) {
                sequencia[tamanho] = valor;
                tamanho++;
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

        // Verificar a validade da sequência
        if (!verificar_sequencia(sequencia, tamanho, k)) {
            printf("\nSequencia: ");
            for (int i = 0; i < tamanho; i++) {
                printf("%d ", sequencia[i]);
            }
            printf("\nJogador %c perdeu.", jogador_atual);
            return 0;
        }

        // Verificar se é uma sequência de vitória
        if (verificar_sequencia_vitoria(sequencia, tamanho, k)) {
            printf("\nSequencia: ");
            for (int i = 0; i < tamanho; i++) {
                printf("%d ", sequencia[i]);
            }
            printf("\nJogador %c ganhou.", jogador_atual);
            return 0;
        }

        // Se a jogada foi válida e não repetida, alterna o jogador
        if (valor > 0) {
            alternar_jogador(&jogador_atual, &conta_jogadas);
        } else {
            // Se a jogada for repetição, aumenta o contador de jogadas repetidas
            conta_jogadas++;
            if (conta_jogadas > 1) { // Não permite mais repetir após 1 vez
                alternar_jogador(&jogador_atual, &conta_jogadas);
            }
        }

        jogadas++;
    }

    // Jogo empatado após K jogadas
    printf("\nSequencia: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", sequencia[i]);
    }
    printf("\nEmpate.");
}