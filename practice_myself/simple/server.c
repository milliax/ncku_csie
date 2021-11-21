#include <stdio.h>
#include <zmq.h>
#include "../lib/json-c/0.15/include/json-c/json.h"
#include <assert.h>
#include <unistd.h>
#include <string.h>

char* get_word_in_json(struct json_object* jobj,char* index){
    struct json_object* word_obj = NULL;
    word_obj = json_object_object_get(jobj,index);
    char* res = malloc(sizeof(char) * 100);
    strcpy(res,json_object_get_string(word_obj));
    return res;
}

int get_int_from_obj(struct json_object* jobj,char* index){
    struct json_object* temp_obj = NULL;
    temp_obj = json_object_object_get(jobj,index);
    const int integer = json_object_get_int(temp_obj);
    return integer;
}

struct json_object* buffer_to_obj(char* buffer){
    struct json_object* jobj = NULL;
    jobj = json_tokener_parse(buffer);
    return jobj;    
}

char* crop_the_letter(char* letter,int start,int end){
    char* toreturn = malloc(sizeof(char) * 100);
    strncpy(toreturn,letter+start,end-start);
    return toreturn;
}

signed main(void){
    char* file_name = "./.env.json";
    struct json_object* para = NULL;
    para = json_object_from_file(file_name);

    void* context = zmq_ctx_new;
    void* host = zmq_socket(context,ZMQ_REP);
    void* client = zmq_socket(context,ZMQ_PUSH);

    printf("[server] Connecting to host.\n");
    int s = zmq_bind(host,get_word_in_json(para,"server_and_host"));
    assert(s == 0);
    printf("[server] Connecting to client\n");
    zmq_connect(client,get_word_in_json(para,"client_to_server"));

    while(1){
        struct json_object* recv = NULL;
        char* buffer = malloc(sizeof(char) * 1000);
        
        zmq_recv(host,buffer,1000,0);

        recv = buffer_to_obj(buffer);

        int length = sizeof(buffer)/sizeof(buffer[0]);
        
        char* letter = get_word_in_json(recv,"letter");
        int section = get_int_from_obj(recv,"section"); 

        // cutting down the sentence.
        for(int i = 0;i < length;++i){
            zmq_send(client,crop_the_letter(letter,i,i+section),section,0);
            i += section;
        }
        sleep(1);
    }

    return 0;
}