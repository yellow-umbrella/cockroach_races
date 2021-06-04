demo: demo.o competition.o player.o cockroach.o utilities.o maze.o ui.o
	g++ -o $@ $^

%.o: %.cpp *.hpp
	g++ -g -c -o $@ $<

clean:
	rm -f *.o demo