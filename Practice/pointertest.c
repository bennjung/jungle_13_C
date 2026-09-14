#include <stdio.h>
#include <stdlib.h>

int main(){
    
    int a = 10;
    int *p = &a;
    int **pp = &p;

    printf("2중 포인터 역참조 -> p의 주소 : %p\n", (void *)pp);
    printf("2중 포인터 역참조 -> a의 주소 : %p\n", (void *)*pp);
    printf("a의 값 %d\n", **pp);
    
    **pp = 5000;

    printf("수정후 a의 값 %d : \n", a);   

    
}