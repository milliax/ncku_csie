#include <stdio.h>
#include <string.h>
#include <stdlib.h>

signed main(void){
    char* arr = "I don' t know who I am.\n";
    char* new_str = malloc(sizeof(char) * 100);
    strncpy(new_str,arr+5,strlen(arr)-5);
    printf("%s",new_str);
}