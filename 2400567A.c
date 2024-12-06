#include <stdio.h>

int main() {
    int k, metade;
    
    // Entrada do valor de K
    printf("Indique K: ");
    scanf("%d", &k);
    
    // Verificação se K está fora do intervalo permitido e imprime o resultado
    if (k < 2 || k > 100) { 
        printf("K tem de ser entre 2 e 100.\n"); 
    } else {
        metade = k / 2; // Calcula a metade de K mas o Diogo eh cabecudo
        printf("Sequencia: %d %d\n", metade, metade); 
    }
}