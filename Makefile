all: oxydium clean

yacc:
	bison -d src/oxydium.yacc -o tmp/oxydium.c

lex:
	flex -o tmp/flex.yy.c src/oxydium.lex

copy:
	cp src/tree/tree_eval.h       	 tmp/tree_eval.h
	cp src/tree/tree.h       				 tmp/tree.h
	cp src/hashmap/hashmap.h 				 tmp/hashmap.h
	cp src/linked_list/linked_list.h tmp/linked_list.h
	cp src/variable_table.h					 tmp/variable_table.h

	cp src/tree/tree_eval.c       	 tmp/tree_eval.c
	cp src/tree/tree.c       				 tmp/tree.c
	cp src/hashmap/hashmap.c				 tmp/hashmap.c
	cp src/linked_list/linked_list.c tmp/linked_list.c
	cp src/variable_table.c					 tmp/variable_table.c



compile: lex yacc copy
	clang -c tmp/tree.c 			 				 		 -o tmp/tree.o
	clang -c tmp/tree_eval.c 			 				 -o tmp/tree_eval.o
	clang -c tmp/flex.yy.c   			 				 -o tmp/flex.o
	clang -c tmp/oxydium.c   			 				 -o tmp/oxydium.o
	clang -c tmp/hashmap.c 				 				 -o tmp/hashmap.o
	clang -c tmp/linked_list.c 						 -o tmp/linked_list.o
	clang -c tmp/variable_table.c					 -o tmp/variable_table.o

oxydium: compile
	clang -o bin/oxydium tmp/*.o -lm

clean:
	rm tmp/*.c tmp/*.h tmp/*.o

run:
	./bin/oxydium -f files/1.ox
