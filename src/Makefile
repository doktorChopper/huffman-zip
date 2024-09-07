CC = gcc
EXE = demo
RM = rm -r
SRCS = ./huffman.c \
	   ./hash_table.c \
	   ./min_heap.c \
	   ./bitset.c \
	   ./main.c \

all: $(EXE)

$(EXE): $(SRCS)
	$(CC) -g3 -o $@ $^

clean:
	$(RM) $(EXE)
