#include <stdio.h>
#include <stdlib.h>
#include <string.h>

signed main(){
    char* arr = (void*) malloc(sizeof(char) *10);
    char* arr2 = (void*) malloc(sizeof(char) *10);
    char* combined = (void*) malloc(sizeof(char) * 20);
    //combined = (void*) calloc(20,sizeof(char));

    char temp = 0;

    printf("combined: %s\n",combined);

    strcpy(arr,"Hello ");
    strcpy(arr2,"World ");

    printf("%s\n",arr);
    printf("%s\n",arr2);

    strncat(arr,arr2,2);
    printf("%s\n",arr);
    
    /* print original string */
    printf("combined: %s\n",combined);

    printf("size of new array: %lu",sizeof(&arr));
    return 0;
}