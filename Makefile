CXX = g++
OBJS = 8puzzle.o NodeBinaryHeap.o Node.o

8puzzle: $(OBJS)
	$(CXX) -Wall -O2 -o $@ $(OBJS)

.cc.o:
	$(CXX) -c -std=c++11 $<

8puzzle.o: BinaryHeap.h NodeBinaryHeap.h Node.h
NodeBinaryHeap.o: BinaryHeap.h NodeBinaryHeap.h Node.h
Node.o: Node.h

clean:
	rm -f *.o
