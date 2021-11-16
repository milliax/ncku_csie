import zmq

context = zmq.Context()

socket = context.socket(zmq.REQ)
socket.connect("tcp://127.0.0.1:7788")

socket.send_string("hello")
print(socket.recv())
