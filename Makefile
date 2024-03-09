# to set the compiler you wish to use, either change this variable or append your make command with CC=<compiler> 
CC = clang++ 
# CC = g++

# to change the linker, either change this variable or append your command with LD=<linker>
LD = mold
# LD = lld
# LD = gold
# LD = bfd


output: main.o snake.o food.o
	$(CC) main.o snake.o food.o -fuse-ld=$(LD) -lraylib -lm -o out

main.o: main.cpp config.hpp
	$(CC) -c main.cpp

snake.o: snake.cpp config.hpp
	$(CC) -c snake.cpp

food.o: food.cpp config.hpp
	$(CC) -c food.cpp

clean:
	rm *.o 
