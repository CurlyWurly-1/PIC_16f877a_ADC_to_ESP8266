# PIC_16f877a_ADC_to_ESP8266

<img src="sintech pic16f877a.jpg" alt="Dev board"/>

Using the development board above, this code reads the voltage on the ADC channel of the pic16f877a (pin RE1) and transmits a value between 0 and 100
using the ESP8266 module (via wifi) to update a Thingspeak graph.
N.B. for pics of the breadboard, please look at the issues (on the right)
N.B. Please note, the following components are required: 

- Pic 16f877a (programmed with the code here)
- 4Mhz crystal 
- 2 X 22pf capacitors (Cap 1 and Cap 2) - any ceramic will do
- Small pushbutton switch (for reset)
- 5V Power supply with wires to connect 5v and ground to breadboard.
- 3.3 volt regulator (TS1086)
- ESP8266 module (Version 1 was used)
- Breadboard (Small breadboard with one side having a power strip - Maplin A101)
- 1k and 2.2k resistors (to divide voltage from 5v to 3.3v for the RX line of the ESP8266)
- 10K resistor - To tie PIC pin 1 to 5V 
- Potentiometer (10K lin) - to supply varying voltage to ADC channel
- Jumper wires


The connections betwwen the various devices are:

PIC
- pic RC6(TX) -> Resistor divider top (1K)
- pic RC7(RX) -> ESP8266 TX pin
- pic Ground  -> ESP8266 Ground
- pic RE1     -> Potentiometer pin 2 (wiper)
- pin 1       -> push button pin 1 and 10K resistor left
- pin 11      -> 5V power supply
- pin 12      -> Ground
- pin 13      -> 4 Mhz crystal left  and Cap 1 right (22pf)
- pin 14      -> 4 Mhz crystal right and Cap 2 right (22pf)

CAPACITORS
- Cap 1 left  (22pf) -> Ground
- Cap 1 right (22pf) -> 4 MHz crystal left  and PIC pin 13
- Cap 2 left  (22pf) -> Ground
- Cap 2 right (22pf) -> 4 MHz crystal right and PIC pin 14 

Push button
- pin 1       -> PIC pin 1 and 10K resistor left
- pin 2       -> Ground

10K resistor
- Left          -> PIC pin 1 and push button pin 1
- Right         -> 5V 

Potentiometer
- pin 1  -> 5V     
- pin 2  -> PIC RE1
- pin 3  -> Ground

Resistor divider
- Resistor divider top (1K)      -> pic RC6 (TX)
- Resistor divider middle        -> ESP8266 RX pin
- Resistor divider bottom (2.2K) -> ESP8266 ground

TS1086 (3.3V regulator)
- TS1086 pin1 (grond)    -> Power supply 0V
- TS1086 pin2 (3.3V out) -> ESP8266 (3.3V Vcc)
- TS1086 pin3 (5V in)    -> Power supply 5V (Also powers pic)

ESP8266
- pin GND   -> pic ground
- pin Vcc   -> TS1086 pin 2 (3.3V)
- pin RX    -> Resistor divider middle
- pin TX    -> pic RC7(RX)
- pin CH_PD -> TS1086 pin 2 (3.3V)

N.B. You also need to set up a thingspeak account, so that you can store the values generated by the pic.
