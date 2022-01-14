# To compile announce to an 32-bit executable, it requires "g++" and/or "g++-multilib" packages installed

all:
	g++ -O2 -c -s -m32 -no-pie *.cpp
	g++ -O2    -s -m32 -no-pie -o announce *.o

debug:
	g++ -O2 -c -g -m32 -no-pie *.cpp
	g++ -O2    -g -m32 -no-pie -o announce_d *.o

clean:
	rm -f *.o
