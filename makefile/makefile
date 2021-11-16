# the make process will only compile the first assigned task no matter what the name is
# If you want to do other tasks just simply type the name
# Eg. make clean

run:hello.cpp
	g++ -c set/a.h
	g++ -c set/b.h
	g++ -o main.out set/main.cpp

test1.out:test1.cpp
	g++ test1.cpp -o test1.out

clean:
	rm -f *.out

clear:
	rm -f *.o