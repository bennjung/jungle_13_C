#include <stdio.h>
#include <stdlib.h>

int main(){
    
    int a = 10;
    int *p = &a;
    char *str = "ABCDEFG";
    // char *p = &str;
    int idx = 0;
    while(str[idx] != '\0'){
        printf("%c ", str[idx]);
        idx++;
    }

    // works same 
    //for(;con;);
    //while(con);

    // works diff
    //for(int i = 10; (printf("%d\n",i ),--i););
    //for(int i = 10; --i;  printf("%d" ,i));
    
}