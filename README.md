## DeviceHub C Library  ##


### Description ###

   DeviceHub C library wraps the DeviceHub MQTT APIs in a easy to use library to be used on resource constrained hardware or C applications

### Requirements ###
   The wrapper depends on paho-mqtt library (an open-source client implementation of MQTT and MQTT-SN messaging protocols)


### Install ###
   For installing the Paho MQTT library for C use this link :

			http://www.eclipse.org/paho/clients/c/

   The C client is built for Linux with cmake and gcc.

   To build:
			
			mkdir build
			cd build
			cmake ..
			make
		

   To install:

			sudo make install



###  RaspberryPi setup ####

			mkdir devel
			sudo apt-get install libssl-dev
			git clone http://git.eclipse.org/gitroot/paho/org.eclipse.paho.mqtt.c.git
			cd org.eclipse.paho.mqtt.c.git
			make
			sudo make install
			sudo apt-get install cmake
			git clone https://github.com/devicehubnet/devicehub_c.git
			cd devicehub_c.git
			mkdir build
			cd build
			cmake..
			make
			sudo make install




###  Test description ####

   To test :

		./devicehub_test # after make , in the build directory


   The test consists of some values published into a "humidity" sensor and "temperature" sensor, also a subscribe on an actuator "light".
   The result can be seen , if you have created the sensors and the actuator with the names mentioned on your account at devicehub before you run this test.
