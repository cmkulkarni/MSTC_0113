#include <stdio.h>

int main (void){
    int i, n, k;

    //What will happen if cond is 1>= 0?
    //Infinite loop

    puts("block 1");
    for(i = 1;i < 256;i = i << 2){
        printf("i = %d \n", i);
    }

    puts("block 2");    
    for(i = 1;i < 256;i <<= 2){
        printf("i = %d \n", i);
    }

    printf("Enter a number: \n");
    scanf("%d", &n);
    printf("Enter a number: \n");
    scanf("%d",&k);
    for(i = 1; i < n ;i = i << k){
        printf("i = %d \n", i);
    }
    for(i = 1; i < n ;i <<= k){
        printf("i = %d \n", i);
    }
    
    return(0);
}