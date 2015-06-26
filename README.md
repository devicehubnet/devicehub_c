## DeviceHub C Library  ##


### Description ###

   DeviceHub C library wraps the DeviceHub MQTT APIs in a easy to use library to be used on resource constrained hardware or C applications

### Requirements ###
   The wrapper depends on Paho library (an open-source client implementation of MQTT and MQTT-SN messaging protocols)


### Install ###
   For installing the Paho library for C use this link :
		
			http://www.eclipse.org/paho/clients/c/ 
   
   The C client is built for Linux with cmake and gcc.
		
   To build:
			
			sudo cmake -G "Unix Makefiles"
			sudo make
		
   To install:
			
			sudo make install
 
		 
   

###  Test description ####
   
   To test : 
			
		./devicehub // after make , in the wrapper library folder
   or 
		
		devicehub // after install 

    
   
   The test consists of some values published into a "humidity" sensor and "temperature" sensor, also a subscribe on an actuator "light".
   The result can be seen , if you have created the sensors and the actuator with the names mentioned on your account at devicehub before you run this test.
