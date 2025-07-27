
all: make run

make: assembler processor

assembler: 
	cd Assembl && make DEB_ASM=0

processor:
	cd Proc && make DEB_STACK=0 PRINT_STACK=0 PROC_DEB=0 PROC_STEP=0 PROC_PRINT=0



run : run_assembler run_processor

run_assembler: 
	cd Assembl && ./Assembler

run_processor:
	cd Proc && ./Processor 


clean: 
	cd Assembl && make clean 
	cd Proc && make clean

