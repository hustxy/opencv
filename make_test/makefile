main: main.o readdirectory.o
	g++ -o main main.o readdirectory.o
main.o: main.cpp readdirectory.h
	g++ -c main.cpp
readdirectory.o: readdirectory.cpp readdirectory.h
	g++ -c readdirectory.cpp
clean: 
	rm *.o













