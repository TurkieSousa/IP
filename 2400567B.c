#include <stdio.h>

#define MAX_SEQ 100

// Função para calcular o produto dos elementos da sequência
int calcular_produto(int *sequencia, int tamanho) {
    int produto = 1;
    for (int i = 0; i < tamanho; i++) {
        produto *= sequencia[i];
    }
    return produto;
}

// Função para calcular a soma dos elementos da sequência
int calcular_soma(int *sequencia, int tamanho) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        soma += sequencia[i];
    }
    return soma;
}

// Função para calcular o valor absoluto
int valor_absoluto(int numero) {
    if (numero < 0) {
        return numero * -1;
    }
    return numero;
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

int main() {
    int k, sequencia[MAX_SEQ], tamanho = 0, num;

    // Entrada do valor de K
    printf("Indique K: ");
    scanf("%d", &k);

    // Entrada da sequência de números inteiros positivos
    printf("Indique uma sequencia de numeros inteiros positivos, terminando com 0: ");
    do {
        scanf("%d", &num);
        if (num < 0) {
            printf("Por favor, insira apenas números inteiros positivos.\n");
        } else if (num != 0) {
            sequencia[tamanho] = num;
            tamanho++;
        }
    } while (num != 0 && tamanho < MAX_SEQ);

    // Verificar o produto e a soma, e a diferença absoluta
    int produto = calcular_produto(sequencia, tamanho);
    int soma = calcular_soma(sequencia, tamanho);
    int diferenca_absoluta = calcular_diferencas_absolutas(sequencia, tamanho);

    if (produto <= k || soma > k) {
        printf("Sequencia invalida\n");
    } else if (diferenca_absoluta == k) {
        printf("Sequencia vitoria\n");
    } else {
        printf("Sequencia valida\n");
    }
}
