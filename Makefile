8puzzle: 8puzzle.o BinaryHeap.o NodeBinaryHeap.o Node.o
	g++ -Wall -O2 8puzzle.o NodeBinaryHeap.o Node.o
8puzzle.o: 8puzzle.cc
	g++ -c 8puzzle.cc

BinaryHeap.o: BinaryHeap.cc
	g++ -c BinaryHeap.cc

NodeBinaryHeap.o: NodeBinaryHeap.cc
	g++ -c NodeBinaryHeap.cc

Node.o: Node.cc
	g++ -c Node.cc

clear:
	rm -rf *.o