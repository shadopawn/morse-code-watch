# Morse Code Watch

[Design Notes](https://docs.google.com/document/d/19emSS7PLROB8-E7uNJGMzSCD_NhitTL9K84vjGpF9SU/edit)

## Dependencies
- [JChristensen/DS3232RTC](https://github.com/JChristensen/DS3232RTC)
- [PaulStoffregen/Time](https://github.com/PaulStoffregen/Time)

## Setup Guides
- [Add Attiny85 board to Arduino IDE](http://highlowtech.org/?p=1695)
- [Tiny AVR Programmer Hookup](https://learn.sparkfun.com/tutorials/tiny-avr-programmer-hookup-guide/all)
- [Software Serial on Attiny85](https://www.youtube.com/watch?v=9CX4i6rMXS8&ab_channel=TomDonnelly)

## Code Snippets
- Set RTC to compile time
    - https://github.com/JChristensen/DS3232RTC/blob/6ef565851c0b1b3c5d0d09a4da19b868906cd01a/examples/alarm_ex1/alarm_ex1.ino#L74
    - https://github.com/arduino-libraries/RTCZero/issues/53
    - https://codebender.cc/sketch:84760#RTC%20SET%20TIME%20TO%20CPU%20TIME.ino
- Put Attiny85 into low power mode
    - [How to achieve low power consumption with Attiny85](https://electronics.stackexchange.com/questions/349496/how-to-achieve-low-power-consumption-with-attiny85)
    - [Attiny Low Power](http://www.technoblogy.com/show?KX0)
    - [A Low Power Attiny85 System](https://community.element14.com/members-area/personalblogs/b/blog/posts/a-low-power-attiny85-system)
- Get internal VCC of Attiny85
    - [ArduinoSystemStatus / SystemStatus.cpp](https://github.com/cano64/ArduinoSystemStatus/blob/master/SystemStatus.cpp)

## Attiny85

![Attiny85 pinout](./images/attiny85_pinout.jpeg)

## Morse Code

![Morse Code](./images/international_morse_code.jpg)
