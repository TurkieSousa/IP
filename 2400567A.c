#include <stdio.h>

int main() {
    int k ;
    
    // Entrada do valor K e a sua divisão
    printf("Indique K: ");
    scanf("%d", &k);
    
    if (k < 2 || k > 100) { 
        printf("K tem de ser entre 2 e 100.\n"); 
    } else 
        printf("Sequencia: %d %d\n", k/2 , k/2); 
}