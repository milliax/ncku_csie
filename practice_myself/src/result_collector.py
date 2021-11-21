from producer import connect_to_consumer
import zmq
import json

def reconstruct_word(buffs):
    r_word = ''
    words = sorted(buffs,key=lambda x:x["index"])
    for word in words:
        r_word += word["word"]
    return r_word

def connect_to_consumer(context,para):
    socket = context.socket(zmq.PULL)
    socket.bind(para['socket_consumer_collector'])
    return socket

def connect_to_system(context,para):
    socket = context.socket(zmq.REQ)
    socket.connect(para["socket_system_server"])
    return socket

def main(para: dict):
    context = zmq.Context()
    socket_consumer = connect_to_consumer(context,para)
    socket_server = connect_to_system(context,para)

    buffs = []

    while True:
        msg = socket_consumer.recv_string()
        jmsg = json.loads(msg)
        buffs.append(jmsg)

        if len(buffs) == jmsg["total_buffers_num"]:
            print("[Collector] All works collected")
            break

    
    word = reconstruct_word(buffs)

    """ Show result """
    print("[Collector] {}".format(word))
    socket_server.send_string("{} e {}".format(para['userID'],para['word']))

if __name__ == "__main__":
    with open('.env.json') as f:
        para = json.load(f)

    main(para)