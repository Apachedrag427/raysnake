output: main.o snake.o food.o
	clang++ main.o snake.o food.o -fuse-ld=mold -lraylib -lm -o out

main.o: main.cpp config.hpp
	clang++ -c main.cpp

snake.o: snake.cpp config.hpp
	clang++ -c snake.cpp

food.o: food.cpp config.hpp
	clang++ -c food.cpp

clean:
	rm *.o 
