import numpy as np

a = [1,2,3,4,5]
v = [1,2,3,4,5]

a = np.array(a)
v = np.array(v)

print(a)
print(v)

full = np.convolve(a,v)
same = np.convolve(a,v,mode="same")
valid = np.convolve(a,v,mode="valid")

print(full)
print(same)
print(valid)