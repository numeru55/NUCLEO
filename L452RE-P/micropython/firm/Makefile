CROSS_COMPILE=~/.platformio/packages/toolchain-gccarmnoneeabi@1.70201.0/bin/arm-none-eabi-
BOARD=NUCLEO_L452RE_P

all:
	git clone https://github.com/micropython/micropython.git
	cd micropython/; git submodule update --init
	cd micropython/mpy-cross/; make -j4
	cp -r ${BOARD} micropython/ports/stm32/boards/
	cd micropython/ports/stm32/; make BOARD=${BOARD} CROSS_COMPILE=${CROSS_COMPILE} -j
	cp micropython/ports/stm32/build-${BOARD}/firmware.bin ./

upload:
	cp micropython/ports/stm32/build-${BOARD}/firmware.bin /Volumes/NODE_L452RE/

clean:
	rm -rf micropython
