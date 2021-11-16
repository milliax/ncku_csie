import os
import zmq
import json

context = zmq.Context()

socket = context.socket(zmq.REP)
socket.connect("tcp://localhost:7788")

print('Worker %s is running ...' % os.getpid())

while True:
    # receive request
    req = socket.recv_json()
    parsed = json.loads(req)
    print(parsed)
    a = int(parsed["a"])
    b = int(parsed["b"])

    print('Compute %s + %s and send response' % (a, b))
    socket.send_string(str(a + b))