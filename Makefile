all: oxydium clean

yacc:
	bison -d src/oxydium.yacc -o tmp/oxydium.c

lex:
	flex -o tmp/flex.yy.c src/oxydium.lex

copy:
	cp src/node_eval.c tmp/node_eval.c
	cp src/node_eval.h tmp/node_eval.h
	cp src/node_tree.c tmp/node_tree.c
	cp src/node_tree.h tmp/node_tree.h

compile: lex yacc copy
	clang -c tmp/node_tree.c -o tmp/node_tree.o
	clang -c tmp/node_eval.c -o tmp/node_eval.o
	clang -c tmp/flex.yy.c   -o tmp/flex.o
	clang -c tmp/oxydium.c   -o tmp/oxydium.o

oxydium: compile
	gcc -o bin/oxydium tmp/*.o

clean:
	rm tmp/*.c tmp/*.h tmp/*.o

run:
	./bin/oxydium -f files/0.ox
