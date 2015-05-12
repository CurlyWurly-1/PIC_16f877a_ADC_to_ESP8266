# PIC_16f877a_ADC_to_ESP8266
This code reads the voltage on the ADC channel of the pic16f877a (pin RE1) and transmits a value between 0 and 100 via wifi
using the ESP8266 module to update a Thingspeak graph

The connections are:
PIC
- pic RC6(TX) -> Resistor divider top (1K)
- pic RC7(RX) -> ESP8266 TX pin
- pic Ground  -> ESP8266 Ground
- pic RE1     -> Potentiometer pin 2 (wiper)

Potentiometer
- pin 1  -> 5V     
- pin 2  -> PIC RE1
- pin 3  -> Ground

Resistor divider
- Resistor divider top (1K)      -> pic RC6 (TX)
- Resistor divider middle        -> ESP8266 RX pin
- Resistor divider bottom (2.2K) -> ESP8266 ground

TS1086 (3.3V regulator)
- TS1086 pin1 (grond)    - Power supply 0V
- TS1086 pin2 (3.3V out) - ESP8266 (3.3V Vcc)
- TS1086 pin3 (5V in)    - Power supply 5V (Also powers pic)

ESP8266
- pin GND   - pic ground
- pin Vcc   - TS1086 pin 2 (3.3V)
- pin RX    - Resistor divider middle
- pin TX    - pic RC7(RX)
- pin CH_PD - TS1086 pin 2 (3.3V)
