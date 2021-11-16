import zmq
import random
import os
import time
import sys

port = 5858

print(sys.argv)

context = zmq.Context()
socket = context.socket(zmq.PUB)

socket.bind("tcp://*:{}".format(port))

print("This is pid: {} speaking".format(os.getpid))

while True:
    topic = random.randrange(9999,10005)
    message_data = random.randrange(1,215) - 80
    print("{} {}".format(topic,message_data))
    socket.send(topic,message_data,sep="\t")
    time.sleep(1)