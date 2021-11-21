import zmq
import json
import time


if __name__ == "__main__":
    with open(".env.json","r") as f:
        para = json.load(f)
    
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    socket.bind(para["socket_system_server"])

    t_start = -1
    t_end = -1

    while True:
        message = socket.recv_string().split()
        
        if len(message) == 2 and message[1] == "s": 
            # start
            ID,info = [str(n) for n in message]
            socket.send_string("{}".format(para['word']))
        elif len(message) == 3 and message[1] == "e":
            # the end
            ID,info,word = [str(n) for n in message]
        else:
            continue

        if info == "s":
            t_start = time.time()
        elif info == "e":
            t_end = time.time()

            socket.close()
            break
        else:
            print("[System] Info unparsable")
        
    # listing the result
    print("[System] {} finished parsing {}".format(para['userID'],para['word']))
    print("[System] time used: {} sec.".format(t_end-t_start))