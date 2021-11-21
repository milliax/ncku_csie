#include <stdio.h>
#include <zmq.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "../lib/json-c/0.15/include/json-c/json.h"

char* retrieve_data(struct json_object* jobj,const char *index){
    struct json_object* word_obj = NULL;
    //printf("index: %s",index);
    //printf("Good\n");
    word_obj = json_object_object_get(jobj,index);

    //const char* res = json_object_get_string(temp);

    char* word = malloc(sizeof(char) * 100);
    strcpy(word,json_object_get_string(word_obj));
    //printf("This is %s",word);
    return word;
}

struct json_object* buffer_to_obj(char* req){
    struct json_object* jobj;
    jobj = json_tokener_parse(req);
    return jobj;
}

signed main(){
    // reading files from json
    char *path = "./.env.json";
    struct json_object* para = NULL;
    //printf("This is path %s\n",path);
    para = json_object_from_file(path);
    //printf("para got!!\n");

    const char* server_port = retrieve_data(para,"client_to_server");

    // establishing network to the server
    void *context = zmq_ctx_new();
    void *server = zmq_socket(context,ZMQ_PULL);

    printf("[client] Connecting to the server\n");
    int s = zmq_connect(server,server_port);
    assert(s == 0);


    while(1){
        struct json_object* jobj;
        char* buffer = malloc(sizeof(char) * 1000);
        
        
        printf("[client] Waiting for jobs\n");
        size_t s = zmq_recv(server,buffer,1000,0);
        
        jobj = buffer_to_obj(buffer);

        char* result = malloc(sizeof(char) * 1000);
        char* action = malloc(sizeof(char) * 100);
        
        result = retrieve_data(jobj,"word");
        

        free(buffer);
    }

    zmq_close(server);
    zmq_ctx_destroy(context);
    return 0;
}