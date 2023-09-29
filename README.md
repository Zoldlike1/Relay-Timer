# Relay-Timer
Simple relay timer that can be added to basically anything. I am using it to automatically disable my soldering iron and bench power supply to avoid a fire hazard incase I forgot to turn them off.

# What does it do?

- Can control mains voltage trough relay module.
- Can display the remaining time on the SSD1306 display
- Has an automatic screen saver that can be adjusted to reduce oled burn.
- Time can be added at customizable amounts using just 1 button. Also toggles screen saver off.

# Whats wrong with it?

- Code is a bit messy, but works.


# How to wire it?

If using arduino nano connect the parts like this (Left is the part side right is arduino);

SSD1306 SCREEN
VCC --> 3.3 V
GND --> GND
SDA --> A4
SCL/SCK --> A5

Relay module

VCC --> 5V
GND --> GND
SIGNAL --> D5

Button (Any 2 pin will work)

Pin 1 --> GND
Pin 2 --> D7
