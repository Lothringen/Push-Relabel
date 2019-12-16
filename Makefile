.PHONY:clean all
CC = g++ 
CCFLAGS = -g -O -std=c++11
RM = rm -f

SRC = push_relabel.cpp 
SRC2 = bfs.cpp
TGT2 = bfs 
TGT = push_relabel


TARGETS = push_relabel bfs

push_relabel:
	$(CC) $(CCFLAGS) -o $(TGT) $(SRC)

bfs:
	$(CC) $(CCFLAGS) -o $(TGT2) $(SRC2)

clean:
	$(RM) *.o
	$(RM) $(TARGETS)
	
