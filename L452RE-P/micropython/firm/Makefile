CROSS_COMPILE=~/.platformio/packages/toolchain-gccarmnoneeabi@1.70201.0/bin/arm-none-eabi-
BOARD=NUCLEO_L452RE_P

all:
	git clone https://github.com/micropython/micropython.git
	cd micropython/; git submodule update --init
	cd micropython/mpy-cross/; make -j4
	#cp -r NUCLEO_L452RE_P micropython/ports/stm32/boards/
	cp -r ${BOARD} micropython/ports/stm32/boards/
	cd micropython/ports/stm32/; make BOARD=${BOARD} CROSS_COMPILE=${CROSS_COMPILE} -j

upload:
	#cp micropython/ports/stm32/build-NUCLEO_L452RE_P/firmware.bin /Volumes/NODE_L452RE/
	cp micropython/ports/stm32/build-${BOARD}/firmware.bin /Volumes/NODE_L452RE/

clean:
	rm -rf micropython
