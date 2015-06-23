
build:
	gcc -g test.c devicehub.c sensorList.c actuatorList.c -o test -lpaho-mqtt3c
	./test

devicehub: 
	gcc -g  devicehub.c sensorList.c actuatorList.c -o devicehu -lpaho-mqtt3c
	./devicehub

sensor:
	gcc -g sensorList.c -o sensor -lpaho-mqtt3c
	./sensor

clean:
	rm -f test devicehub sensor
