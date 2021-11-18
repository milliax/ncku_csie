#include <stdio.h>
#include <json.h>

int read_from_json_file(char *filename){
    int ret = 0;
    json_object *test_obj = NULL;
    json_object *tmp_obj = NULL;
    json_object *tmp1_obj = NULL;
    json_object *tmp2_obj = NULL;

    test_obj = json_object_from_file(filename);
    if(!test_obj){
        printf("Cannot open %s\n",filename);
    }
}

signed main(void){

    return 0;
}

