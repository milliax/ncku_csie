#include<zmq.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<unistd.h>

signed main(void){
    void *context = zmq_ctx_new();
    void *responder = zmq_socket(context,ZMQ_REP);

    int rc = zmq_bind(responder,"tcp://*:5555");
    assert(rc == 0);

    while(1){
        char buffer[10];
        zmq_recv(responder,buffer,10,0);
        printf("Recieved!!\n");
        sleep(1);
        zmq_send(responder,"This is weird",13,0);
    }
    return 0;
}