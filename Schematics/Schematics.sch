EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20PU U?
U 1 1 60F8DA9A
P 5550 4150
F 0 "U?" H 5021 4196 50  0000 R CNN
F 1 "ATtiny85-20PU" H 5021 4105 50  0000 R CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5550 4150 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 5550 4150 50  0001 C CNN
	1    5550 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F8F914
P 5550 4750
F 0 "#PWR?" H 5550 4500 50  0001 C CNN
F 1 "GND" H 5555 4577 50  0000 C CNN
F 2 "" H 5550 4750 50  0001 C CNN
F 3 "" H 5550 4750 50  0001 C CNN
	1    5550 4750
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 60F9015E
P 5550 3550
F 0 "#PWR?" H 5550 3400 50  0001 C CNN
F 1 "VCC" H 5565 3723 50  0000 C CNN
F 2 "" H 5550 3550 50  0001 C CNN
F 3 "" H 5550 3550 50  0001 C CNN
	1    5550 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 60F91FAD
P 7700 4150
F 0 "J?" H 7780 4192 50  0000 L CNN
F 1 "IR Sensor" H 7780 4101 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7700 4150 50  0001 C CNN
F 3 "~" H 7700 4150 50  0001 C CNN
	1    7700 4150
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 60F92FA8
P 7500 4150
F 0 "#PWR?" H 7500 4000 50  0001 C CNN
F 1 "VCC" V 7515 4277 50  0000 L CNN
F 2 "" H 7500 4150 50  0001 C CNN
F 3 "" H 7500 4150 50  0001 C CNN
	1    7500 4150
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F9362D
P 7500 4250
F 0 "#PWR?" H 7500 4000 50  0001 C CNN
F 1 "GND" V 7505 4122 50  0000 R CNN
F 2 "" H 7500 4250 50  0001 C CNN
F 3 "" H 7500 4250 50  0001 C CNN
	1    7500 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	7500 4050 6150 4050
Text Label 6950 4050 0    50   ~ 0
IR_Signal
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 60F9468A
P 7700 3750
F 0 "J?" H 7780 3792 50  0000 L CNN
F 1 "Relay" H 7780 3701 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7700 3750 50  0001 C CNN
F 3 "~" H 7700 3750 50  0001 C CNN
	1    7700 3750
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 60F950A0
P 7500 3750
F 0 "#PWR?" H 7500 3600 50  0001 C CNN
F 1 "VCC" V 7515 3877 50  0000 L CNN
F 2 "" H 7500 3750 50  0001 C CNN
F 3 "" H 7500 3750 50  0001 C CNN
	1    7500 3750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60F9543F
P 7500 3850
F 0 "#PWR?" H 7500 3600 50  0001 C CNN
F 1 "GND" V 7505 3722 50  0000 R CNN
F 2 "" H 7500 3850 50  0001 C CNN
F 3 "" H 7500 3850 50  0001 C CNN
	1    7500 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	7500 3650 6950 3650
Wire Wire Line
	6950 3650 6950 3950
Wire Wire Line
	6950 3950 6150 3950
Text Label 6950 3650 0    50   ~ 0
Relay_Signal
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 60F97C35
P 7700 4600
F 0 "J?" H 7780 4642 50  0000 L CNN
F 1 "BB_I2C" H 7780 4551 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7700 4600 50  0001 C CNN
F 3 "~" H 7700 4600 50  0001 C CNN
	1    7700 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 4150 6950 4150
Wire Wire Line
	6950 4150 6950 4500
Wire Wire Line
	6950 4500 7500 4500
Wire Wire Line
	7500 4600 6900 4600
Wire Wire Line
	6900 4600 6900 4250
Wire Wire Line
	6900 4250 6150 4250
Text Label 7000 4600 0    50   ~ 0
SDA
Text Label 7000 4500 0    50   ~ 0
SCL
$Comp
L power:GND #PWR?
U 1 1 60F991EA
P 7500 4700
F 0 "#PWR?" H 7500 4450 50  0001 C CNN
F 1 "GND" V 7505 4572 50  0000 R CNN
F 2 "" H 7500 4700 50  0001 C CNN
F 3 "" H 7500 4700 50  0001 C CNN
	1    7500 4700
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60F9C7EE
P 6350 5200
F 0 "R?" H 6280 5154 50  0000 R CNN
F 1 "20K" H 6280 5245 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P1.90mm_Vertical" V 6280 5200 50  0001 C CNN
F 3 "~" H 6350 5200 50  0001 C CNN
	1    6350 5200
	-1   0    0    1   
$EndComp
$Comp
L Device:C C?
U 1 1 60F9D708
P 6350 5500
F 0 "C?" H 6465 5546 50  0000 L CNN
F 1 "0.1u" H 6465 5455 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P2.50mm" H 6388 5350 50  0001 C CNN
F 3 "~" H 6350 5500 50  0001 C CNN
	1    6350 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 5350 6350 5350
Wire Wire Line
	6150 4350 6150 5350
Connection ~ 6350 5350
$Comp
L power:GND #PWR?
U 1 1 60F9E0EB
P 6350 5650
F 0 "#PWR?" H 6350 5400 50  0001 C CNN
F 1 "GND" H 6355 5477 50  0000 C CNN
F 2 "" H 6350 5650 50  0001 C CNN
F 3 "" H 6350 5650 50  0001 C CNN
	1    6350 5650
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 60F9E6B1
P 6350 5050
F 0 "#PWR?" H 6350 4900 50  0001 C CNN
F 1 "VCC" H 6365 5223 50  0000 C CNN
F 2 "" H 6350 5050 50  0001 C CNN
F 3 "" H 6350 5050 50  0001 C CNN
	1    6350 5050
	1    0    0    -1  
$EndComp
Text Label 6150 5350 1    50   ~ 0
RESET
$Comp
L Regulator_Linear:L7805 U?
U 1 1 60FA27FD
P 3250 5600
F 0 "U?" H 3250 5842 50  0000 C CNN
F 1 "L7805" H 3250 5751 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 3275 5450 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 3250 5550 50  0001 C CNN
	1    3250 5600
	1    0    0    -1  
$EndComp
$Comp
L Simulation_SPICE:VDC V?
U 1 1 60FA39C1
P 2650 5950
F 0 "V?" H 2780 6041 50  0000 L CNN
F 1 "Vin" H 2780 5950 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2650 5950 50  0001 C CNN
F 3 "~" H 2650 5950 50  0001 C CNN
F 4 "Y" H 2650 5950 50  0001 L CNN "Spice_Netlist_Enabled"
F 5 "V" H 2650 5950 50  0001 L CNN "Spice_Primitive"
F 6 "dc(1)" H 2780 5859 50  0000 L CNN "Spice_Model"
	1    2650 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 5750 2650 5600
Wire Wire Line
	2650 5600 2950 5600
Wire Wire Line
	2650 6150 2950 6150
Wire Wire Line
	3250 6150 3250 5900
$Comp
L power:GND #PWR?
U 1 1 60FA4945
P 2950 6150
F 0 "#PWR?" H 2950 5900 50  0001 C CNN
F 1 "GND" H 2955 5977 50  0000 C CNN
F 2 "" H 2950 6150 50  0001 C CNN
F 3 "" H 2950 6150 50  0001 C CNN
	1    2950 6150
	1    0    0    -1  
$EndComp
Connection ~ 2950 6150
Wire Wire Line
	2950 6150 3250 6150
$Comp
L power:VCC #PWR?
U 1 1 60FA501B
P 3550 5600
F 0 "#PWR?" H 3550 5450 50  0001 C CNN
F 1 "VCC" H 3565 5773 50  0000 C CNN
F 2 "" H 3550 5600 50  0001 C CNN
F 3 "" H 3550 5600 50  0001 C CNN
	1    3550 5600
	0    1    1    0   
$EndComp
Text Notes 2300 4950 0    50   ~ 0
Voltage regulator
Text Notes 4400 3300 0    50   ~ 0
Main Circuit
Wire Notes Line
	2300 4950 3900 4950
Wire Notes Line
	3900 4950 3900 6500
Wire Notes Line
	3900 6500 2300 6500
Wire Notes Line
	2300 6500 2300 4950
Wire Notes Line
	4400 3300 8350 3300
Wire Notes Line
	8350 3300 8350 5900
Wire Notes Line
	8350 5900 4400 5900
Wire Notes Line
	4400 5900 4400 3300
$EndSCHEMATC
