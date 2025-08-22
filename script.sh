nasm -felf64 $1.asm

gcc -no-pie $1.o -o ready -z noexecstack

rm $1.o
