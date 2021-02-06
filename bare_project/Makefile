
all:
	make -C drv
	make -C init
	make -C tool
	./mkbl2 init/stage2.bin bl2.bin	
	mv bl2.bin arm.bin ./target/
	rm -f mkbl2
clean:
	make -C drv clean
	make -C init clean
	make -C tool clean
