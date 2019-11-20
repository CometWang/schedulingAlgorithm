#Makefile for the assignment

all: part1 part2


part1:part1.c
	gcc -o part1.out part1.c -pthread

part2:part2_2.out part2_1.out
	gcc -o part2.out part2_1.out part2_2.out

part2_2.out:part2_2.c scheduling.h
	gcc -c part2_2.c -o part2_2.out

part2_1.out:part2_1.c scheduling.h
	gcc -c part2_1.c -o part2_1.out

clean:
	rm -f part1 part2 cpu_scheduling_output_file.txt *.out *.o core

