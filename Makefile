all: task

task: task6_c.o task6_asm.o
	@ gcc -m32 task6_c.o task6_asm.o -o task6

task6_c.o: task6.c
	@ gcc -m32 -c task6.c -o task6_c.o

task6_asm.o: task6.asm
	@ nasm task6.asm -f elf32 -o task6_asm.o

clean:
	@ rm -rf *.o task6