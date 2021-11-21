#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <zmq.h>
#include "../lib/json-c/0.15/include/json-c/json.h"

struct json_object* load_system_parameters(const char* path){
    struct json_object* para = NULL;
    int fd;

    para = json_object_from_file(path);
    return para;
}

const char* get_addr_from_para(struct json_object* jobj, const char* name){
    struct json_object* info = NULL;
    info = json_object_object_get(jobj,name);
    const char* addr = json_object_get_string(info);
    return addr;
}

char* get_word_from_json_object(struct json_object* jobj){
    struct json_object* word_obj = NULL;
    char* word = malloc(sizeof(char) * 100);

    word_obj = json_object_object_get(jobj,"word");
    strcpy(word,json_object_get_string(word_obj));

    return word;
}

void fill_word_in_json(struct json_object* jobj,char* new_word){
    json_object_object_add(
        jobj,
        "word",
        json_object_new_string(new_word)
    );
}
struct json_object* Work(char* buf){
    struct json_object* rjobj;
    char* word;
    char new_word[1000];

    rjobj = json_tokener_parse(buf);
    word = get_word_from_json_object(rjobj);

    strcpy(new_word, word);
    strcat(new_word, word);

    fill_word_in_json(rjobj,new_word);
    return rjobj;
}


/* This is where the main program begins */
int main(void){
    printf("[Consumer] Loading system parameters\n");
    // json
    struct json_object* para = load_system_parameters("./.env.json");
    // zmq
    const char* addr_producer_consumer = get_addr_from_para(para,"socket_producer_consumer");
    const char* addr_consumer_collector = get_addr_from_para(para,"socket_consumer_collector");

    // connection settings
    void* context = zmq_ctx_new();
    void* socket_producer = zmq_socket(context,ZMQ_PULL);
    void* socket_collector = zmq_socket(context,ZMQ_PUSH);
    printf("[Consumer] Connecting to Producer\n");
    zmq_connect(socket_producer,addr_producer_consumer);
    printf("[Consumer] Connecting to Collector\n");
    int s = zmq_connect(socket_collector, addr_consumer_collector);

    while(1){
        struct json_object* work;
        void* buffer = (void*) malloc(1000 * sizeof(char));
        printf("[Consumer] waiting for new work\n");
        
        size_t s = zmq_recv(socket_producer,buffer,1000,0);
        work = Work((char*) buffer);

        const char* msg = json_object_to_json_string(work);
        zmq_send(socket_collector,msg,strlen(msg),0);
        free(buffer);
    }

    zmq_close(socket_collector);
    zmq_close(socket_producer);
    zmq_ctx_destroy(context);


    return 0;
}