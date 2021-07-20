#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include<string.h>

void reverse_array(int *pa, int n);
void get_reveresed_array(int *pa, int n, int** pp_ra);
void get_subarray(int *pa, int , int i, int j, int** pp_sub_array, int* p_n);
void get_reversed_subarray(int *pa, int n,int i, int j, int** pp_reversed_sub_array, int* p_n);
void get_array_slice(int* pa, int n, int i, int j, int k, int** pp_slice, int* p_n);

void test_basic_routines(void);
void test_reverse_routines(void);
void test_subarray_routines(void);
void test_slice_routines(void);

void show(int *pa, int n, const char* msg);

int main(void){
    test_basic_routines();
    test_reverse_routines();
    test_subarray_routines();
    test_slice_routines();
    return (0);
}

void test_basic_routines(void)
{
    #define ARR_SIZE 10
    int a[ARR_SIZE] = {10, 15, 20, 25, 30, 35, 40, 45, 50, 55};
    int i;

    puts("print array in forward direction");
    for(i = 0; i< ARR_SIZE; ++i)
        printf("a[%d]:%d\n", i, a[i]);

    puts("printing array in backward direction");
    for(i = ARR_SIZE-1 ; i >= 0 ; --i)
        printf("a[%d]:%d\n", i, a[i]);

    puts("Print all even indices -> forward");
    for(i = 0; i< ARR_SIZE; i+=2)
        printf("a[%d]:%d\n", i, a[i]);

    puts("Print all odd indices -> forward");
    for(i = 1; i< ARR_SIZE; i+=2)
        printf("a[%d]:%d\n", i, a[i]);
}

void test_reverse_routines(void){
    #ifdef ARR_SIZE
    #undef ARR_SIZE
    #define ARR_SIZE 5
    #endif

    int a[ARR_SIZE] = {10, 20, 30 ,40 ,50};
    int * p_ra=NULL;

    show(a, ARR_SIZE, "array a:");
    get_reveresed_array(a, ARR_SIZE, &p_ra);
    show(p_ra, ARR_SIZE, "Reversed version of a:");
    free(p_ra);
    p_ra = NULL;
    reverse_array(a, ARR_SIZE);
    show(a, ARR_SIZE, "Array 'a' reversed in place:");
}

void test_subarray_routines(void){
    #ifdef ARR_SIZE
    #undef ARR_SIZE
    #define ARR_SIZE 10
    #endif
    
    int a[ARR_SIZE] = {10, 15, 20, 25, 30, 35,40, 45, 50, 55};
    int* p_sub_arr = NULL;
    int* p_reversed_sub_array = NULL;
    int n = 0;

    show(a, ARR_SIZE, "Original Array:");
    get_subarray(a, ARR_SIZE, 3, 7, &p_sub_arr, &n);
    if(p_sub_arr)
        show(p_sub_arr, n, "Showing sub_array = a[3:7]");
    free(p_sub_arr);
    p_sub_arr = NULL;
    n = 0;
    get_reversed_subarray(a, ARR_SIZE, 3, 7, &p_reversed_sub_array, &n);
    if(p_reversed_sub_array)
        show(p_reversed_sub_array, n , "Showing reversed sub array = a[3:7]");

    free(p_reversed_sub_array);
    p_reversed_sub_array = NULL;
    n=0;
}

void test_slice_routines(void)
{
    #ifdef ARR_SIZE
    #undef ARR_SIZE
    #define ARR_SIZE 10
    #endif
    int a[ARR_SIZE] = {10, 15, 20, 25,30,35,40,45,50,55};
    int * p_slice = NULL;
    int n = 0;
    show(a, ARR_SIZE, "Original Array");
    get_array_slice(a, ARR_SIZE, 1, 8, 2, &p_slice, &n);
    if(p_slice)
        show(p_slice, n, "Slice of a:a[1:8:2]:");
    free(p_slice);
    p_slice = NULL;
}

void reverse_array(int *p, int n)
{
    int i;
    int tmp;

    for(i = 0; i < (n-1)/2; i++)
    {
        tmp = p[i];
        p[i] = p[n-1-i];
        p[n-1-i] = tmp;
    }
}

void get_reveresed_array(int * pa, int n, int** pp_ra)
{   
    int* p_new_arr = NULL;
    int i;

    p_new_arr = (int*)malloc(n * sizeof(int));
    assert(p_new_arr);
    memset(p_new_arr, 0, n* sizeof(int));
    for(i = 0; i < n; ++i)
    {
        p_new_arr[i] = pa[n-1-i];
    }
    *pp_ra = p_new_arr;
}

void get_subarray(int * pa, int n, int i, int j, int** pp_sub_array, int *p_n)
{
    int* p_sub_array;
    int len_sub_array;
    int k, r;

    if(n <= 0 || i < 0 || j < 0 || i> n-1 || j > n || i >= j)
    {
        *pp_sub_array = NULL;
        *p_n = 0;
    }
    len_sub_array = j - i;
    p_sub_array = (int*)malloc(len_sub_array * sizeof(int));
    assert(p_sub_array);
    memset(p_sub_array, 0, len_sub_array * sizeof(int));
    for(k = 0, r = i; r < j; ++k, ++r)
        p_sub_array[k] = pa[r];
    *pp_sub_array = p_sub_array;
    *p_n = len_sub_array;
}

void get_reversed_subarray(int* pa, int n, int i, int j, int** pp_reversed_sub_array, int* p_n)
{
    int* p_sub_array;
    int len_sub_array;
    int k, r;

    if(n <= 0 || i < 0 || j < 0 || i > n-1 || j > n || i >= j)
    {
        *pp_reversed_sub_array = NULL;
        *p_n = 0;
    }
    len_sub_array = j-i;
    p_sub_array = (int*)malloc(len_sub_array * sizeof(int));
    assert(p_sub_array);
    memset(p_sub_array, 0, len_sub_array *sizeof(int));
    for(k = j - 1, r = 0; k >= i -1; --k, ++r)
    {
        p_sub_array[r] = pa[k];
    }
    *pp_reversed_sub_array = p_sub_array;
    *p_n = len_sub_array;
}

void get_array_slice(int * pa, int n, int i, int j, int k, int ** pp_slice, int *p_n)
{
    int* p_slice = NULL;
    int slice_len =0;
    int p, q;

    if( i < 0 || j < 0 || k <= 0|| i > n - 1 || j > n || i >= j)
    {
        *pp_slice = NULL;
        *p_n = 0;
        return;
    }
    slice_len = ceilf((j - i) / (float)k);
    p_slice = (int*)malloc(slice_len * sizeof(int));
    assert(p_slice);
    memset(p_slice, 0, slice_len * sizeof(int));
    for(p = i, q = 0; p < j; p = p + k, ++q)
        p_slice[q] = pa[p];
    *pp_slice = p_slice;
    *p_n = slice_len; 
}

void show(int* pa, int n, const char *msg)
{
    int i;
    if(msg)
        puts(msg);
    for(i = 0; i< n; ++i)
        printf("a[%d]:%d\n", i, pa[i]);
}
