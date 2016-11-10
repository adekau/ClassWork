FILENAME = bdsp.c

main: ${FILENAME}
	msp430-gcc -mmcu=msp430g2553 ${FILENAME} -g -o button.elf

flash: button.elf
	mspdebug rf2500 'prog button.elf'

clean:
	rm -rf *.o *.elf *.out

erase:
	mspdebug rf2500 erase

debug: button.elf
	(mspdebug rf2500 "gdb" 1>/dev/null &); msp430-gdb button.elf -ex "target remote :2000"
