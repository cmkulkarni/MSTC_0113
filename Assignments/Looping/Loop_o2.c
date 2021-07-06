#include <stdio.h>

int main (void){
    int i, n, k;

    puts("block 1");
    for(i = 5;i > 0;i--){
        printf("i = %d \n", i);
    }

    puts("block 2");
    for(i = 5; i>0; --i){
        printf("i = %d\n", i);
    }

    puts("block 3");
    for(i = 10;i > 0; i -= 2){
        printf("i = %d\n", i);
    }
    
    puts("block 4");
    for(i = 10;i > 0; i = i - 2){
        printf("i = %d\n", i);
    }

    puts("block 5");
    printf("Enter a number: \n");
    scanf("%d", &n);
    printf("Enter a number: \n");
    scanf("%d",&k);
    for(i = n;i > 0; i -= k){
        printf("i = %d\n", i);
    }

    
    return(0);
}