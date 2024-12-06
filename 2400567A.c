#include <stdio.h>

int main() {
    int k, metade;
    
    printf("Indique K: ");
    scanf("%d", &k);
    
    if (k < 2 || k > 100) { 
        printf("K tem de ser entre 2 e 100.\n"); 
    } else {
        metade = k / 2; 
        printf("Sequencia: %d %d\n", metade, metade); 
    }
}