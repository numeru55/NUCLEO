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

CORE = STMicroelectronics:stm32:Nucleo_64:pnum=NUCLEO_G070RB
#CORE = STMicroelectronics:stm32:GenG0

PORT = /dev/cu.usbmodem14103

compile:
	arduino-cli compile --fqbn ${CORE} ${TARGET}

upload: compile
	arduino-cli upload --fqbn ${CORE} ${TARGET}

monitor:
	sleep 1;
	arduino-cli monitor -p ${PORT}

URL = https://github.com/tenbaht/sduino/raw/master/package_sduino_stm8_index.json

setup:
	# brew update
	# brew install arduino-cli
	arduino-cli core update-index --additional-urls ${URL}
	arduino-cli core search stm8 --additional-urls ${URL}
	arduino-cli core install sduino:stm8 --additional-urls ${URL}
	#arduino-cli board listall # show available board
	#arduino-cli board list # show connected board
	# arduino-cli lib search u8g2
	#arduino-cli lib install "STM32duino FreeRTOS" --additional-urls http://dan.drown.org/stm32duino/package_STM32duino_index.json # for FreeRTOS
