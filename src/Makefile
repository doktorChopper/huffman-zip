CC = gcc
EXE = demo

all: $(EXE)

$(EXE): ./hash_table.c ./main.c
	$(CC) -g3 -o $@ $^

clean:
	rm -r $(EXE)
