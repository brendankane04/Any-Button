# Any Button
With this device, you can make any pushbutton or switch on a home appliance *remote controlled!* 

Simply connect the leads of the button of the appliance to the relay on this device, and it will make the device remote-operated.

## Materials:

1. [VS1838 IR Receiver](https://datasheetspdf.com/pdf-file/700398/ETC/VS1838B/1) <br>
2. [IR Remote (MP3 Control)](https://www.amazon.com/KOOBOOK-Infrared-Wireless-Control-Receiver/dp/B07S67SFSF/ref=pd_sbs_1/140-3142093-1069413?pd_rd_w=dmh5y&pf_rd_p=0a3ad226-8a77-4898-9a99-63ffeb1aef90&pf_rd_r=679X1BYENFA4Q5D7KPQT&pd_rd_r=20a569e2-5dc0-4ce2-99c9-b3cc044566fd&pd_rd_wg=Kmetr&pd_rd_i=B07S67SFSF&psc=1) <br>
3. [Attiny85, DIP package](https://www.amazon.com/Original-Atmel-Dip-8-ATTINY85-20PU-Tiny85-20Pu/dp/B06W9JBJJ6/ref=sr_1_3?dchild=1&keywords=attiny85&qid=1628904159&sr=8-3) <br>
4. [L7805 5V Voltage regulator](https://www.amazon.com/Pieces-Voltage-Regulator-Linear-Positive/dp/B07RB251DC/ref=sr_1_4?dchild=1&keywords=L7805&qid=1628904211&sr=8-4) <br>
5. Various Electical Components <br> 

## Firmware: 

This file system is a project which can be conveniently opened in Atmel Studio 7 with the following important source files:

### Files:

-**main.cpp:** Main file<br>
-**IR_Receiver.cpp:** Driver for the IR Receiver connected to the INT0 pin. It receives IR commands based on the IR-NEC protocol<br>
-**Relay.cpp:** Driver for the relay which simulates the switch or button<br>
-**Lever.cpp:** Driver for a relay which controls a solenoid attached to a lever. This requires more physical set up & hardware but doesn't necessitate directly wiring to the appliance.<br>
-**BB\_I2C.cpp:** Driver for a rudimentary pseudo-I2C communication protocol. It was written to make debugging easier.<br>

## Schematics:

This file system contains a project which builds the schematic design & the board layout of the device. 
The project can opened with kicad.

The device may be connected to the appliance by attaching a >= 5V line or by using an independent voltage source.

It uses default parts & layouts. Consequently, it has no custom libraries.

The final product can be conveniently viewed in the form of PDF's

### PDF's:

-**Schematic.pdf:** Image of the schematics <br>
-**Layout.pdf:** Image of the board layout <br>
