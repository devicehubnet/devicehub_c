
build:
	gcc -g devicehub.c sensorList.c actuatorList.c -o devicehub -lpaho-mqtt3c
	./devicehub

sensor:
	gcc -g sensorList.c -o sensor -lpaho-mqtt3c
	./sensor

clean:
	rm -f devicehub sensor
