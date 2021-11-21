import time
times = int(10E7)
print(times)
array1 = [str(i) for i in range(times)]
array2 = [str(i) for i in range(times)]

print("initialized")

""" section 1 """

print("mapping out the data")
start_time = time.time()
array1 = list(map(int,array1))
end_time = time.time()

print("Processed time is {}".format(end_time-start_time))

""" section 2 """
print("for the data")
start_time = time.time()
array2 = [int(i) for i in array2]
end_time = time.time()

print("Processed time is {}".format(end_time-start_time))