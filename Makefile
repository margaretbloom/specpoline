ASM_FLAGS=-felf64 spec.asm
C_FLAGS=-Wall -Wextra -Wpedantic -std=c11 main.c

obj_spec: spec.asm
	nasm ${ASM_FLAGS} -DSPEC_STORE -o spec.o

obj_arch: spec.asm
	nasm ${ASM_FLAGS} -DARCH_STORE -o arch.o

spec: obj_spec
	gcc ${C_FLAGS} spec.o -o spec
arch: obj_arch
	gcc ${C_FLAGS} arch.o -o arch

run_spec: spec
	./spec

run_arch: arch
	./arch

clean:
	rm *.o
