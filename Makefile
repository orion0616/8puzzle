CXX = g++
OBJS = 8puzzle.o NodeBinaryHeap.o Node.o

8puzzle: $(OBJS)
	$(CXX) -Wall -O2 -o $@ $(OBJS)

.cc.o:
	$(CXX) -c $<

8puzzle.cc: BinaryHeap.h NodeBinaryHeap.h Node.h
NodeBinaryHeap.cc: BinaryHeap.h NodeBinaryHeap.h Node.h
Node.cc: Node.h

clean:
	rm -f *.o
