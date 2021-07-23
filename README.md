# Any Button
With this device, you can make any pushbutton or switch on a home appliance *remote controlled!* 

Simply connect the leads of the button of the appliance to the relay on this device, and it will make the device remote-operated.

## Materials:

1. VS1838 IR Receiver <br>
2. IR Remote (MP3 Control) <br>
3. Attiny85, DIP package <br>
4. L7805 5V Voltage regulator <br>
5. Capacitors <br> 
6. Resistors 

## Firmware: 

This file system is a project which can be conveniently opened in Atmel Studio 7 with the following important source files:

### Files:

-**main.cpp:** Main file<br>
-**IR_Receiver.cpp:** Driver for the IR Receiver connected to the INT0 pin<br>
-**Relay.cpp:** Driver for the relay which simulates the switch or button<br>
-**BB\_I2C.cpp:** Driver for a rudimentary pseudo-I2C communication protocl. It was written to make debugging easier.<br>

## Schematics:

This files system contains a project which designs the schematic design & the board layout of the device. 
The project can opened with kicad.

It uses default parts & layouts. Consequently, it has no custom libraries.

The final product can be conveniently viewed in the form of PDF's

### PDF's:

-**Schematic.pdf:** Image of the schematics <br>
-**Layout.pdf:** Image of the board layout <br>