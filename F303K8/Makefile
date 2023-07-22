# usage:
#
# make                 # build only
# make upload          # build and upload
# make upload monitor  # build, upload and then monitor
# make setup
#
# make TARGET = MyFirstSketch   # change target

#TARGET = hello_NUCLEO_G070RB
#TARGET = blink_PA5
TARGET = i2c_scan

CORE = STMicroelectronics:stm32:Nucleo_32:pnum=NUCLEO_F303K8
#CORE = STMicroelectronics:stm32:GenG0

PORT = /dev/cu.usbmodem14103

compile:
	arduino-cli compile --fqbn ${CORE} ${TARGET}

upload: compile
	arduino-cli upload --fqbn ${CORE} ${TARGET}

monitor:
	sleep 1;
	arduino-cli monitor -p ${PORT}

URL = https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json

setup:
	# brew update
	# brew install arduino-cli
	arduino-cli core update-index --additional-urls ${URL}
	arduino-cli core install STMicroelectronics:stm32 --additional-urls ${URL}
	#arduino-cli board listall # show available board
	#arduino-cli board list # show connected board
	# arduino-cli lib search u8g2
	arduino-cli lib install "STM32duino FreeRTOS" --additional-urls http://dan.drown.org/stm32duino/package_STM32duino_index.json # for FreeRTOS
