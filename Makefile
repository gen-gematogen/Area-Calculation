all: task

task: task6_cpp.o task6_asm.o
	@ g++ -m32 task6_cpp.o task6_asm.o -o task6

task6_cpp.o: task6.cpp
	@ g++ -m32 -c task6.cpp -o task6_cpp.o

task6_asm.o: task6.asm
	@ nasm task6.asm -f elf32 -o task6_asm.o

clean:
	@ rm -rf *.o task6