#include <stdio.h>

int main (void){
    int i, j;
    int m = 8, n= 6;

    //What will happen if cond is 1>= 0?
    //Infinite loop

    puts("block 1");
    for(i = 0;i < m; ++i){
        for(j = 0;j < n; ++j){
            if((i + j) < (m+n)/2)
                printf("i = %d, j = %d \n", i, j);
        }
    }

    puts("block 2");
    for(i = 0;i < m; ++i){
        for(j = 0;j < n; ++j){
            if((i + j) <= (m+n)/2)
                printf("i = %d, j = %d \n", i, j);
        }
    }

    puts("block 3");
    for(i = 0;i < m; ++i){
        for(j = 0;j < n; ++j){
            if((i - j) <= (m+n)/2)
                printf("i = %d, j = %d \n", i, j);
        }
    }

    puts("block 4");
    for(i = 0;i < m; ++i){
        for(j = 0;j < n; ++j){
            if((i - j) < (m+n)/2)
                printf("i = %d, j = %d \n", i, j);
        }
    }

    puts("block 5");
    for(i = 0;i < m; ++i){
        for(j = 0;j < n; ++j){
            if((i * j) <= (m+n)/2)
                printf("i = %d, j = %d \n", i, j);
        }
    }

    puts("block 6");
    for(i = 0;i < m; ++i){
        for(j = 0;j < n; ++j){
            if((i * j) <= (n-1)*(m-1))
                printf("i = %d, j = %d \n", i, j);
        }
    }    
    
    return(0);
}