import os
import subprocess
import json

""" reading from environment variables """
with open('./.env.json',"r") as f:
    para = json.load(f)

""" compile consumer """
s = os.system("make")
assert s == 0, "Can not compile consumer"

""" system """
p_judg = subprocess.Popen(["python3",".judge.py"])

""" User defined """
p_cons = []

for i in range(para["num_of_consumers"]):
    p = subprocess.Popen(["./consumer"])
    p_cons.append(p)
p_coll = subprocess.Popen(["python3","result_collector.py"])
p_prod = subprocess.Popen(["python3","producer.py"])

""" waiting for all processes to stop """
while p_coll.poll() == None:
    continue

""" kill opened processes """

for i in p_cons:
    p.kill()

p_judg.kill()
p_prod.kill()
p_coll.kill()