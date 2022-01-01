# Morse Code Watch

[Design Notes](https://docs.google.com/document/d/19emSS7PLROB8-E7uNJGMzSCD_NhitTL9K84vjGpF9SU/edit)

## Dependencies

- [JChristensen/DS3232RTC](https://github.com/JChristensen/DS3232RTC)

## Setup Guides
- [Add Attiny85 board to Arduino IDE](http://highlowtech.org/?p=1695)
- [Tiny AVR Programmer Hookup](https://learn.sparkfun.com/tutorials/tiny-avr-programmer-hookup-guide/all)
- [Software Serial on Attiny85](https://www.youtube.com/watch?v=9CX4i6rMXS8&ab_channel=TomDonnelly)

## Code Snippets
- Set RTC to compile time
    - https://github.com/JChristensen/DS3232RTC/blob/6ef565851c0b1b3c5d0d09a4da19b868906cd01a/examples/alarm_ex1/alarm_ex1.ino#L74
    - https://github.com/arduino-libraries/RTCZero/issues/53
    - https://codebender.cc/sketch:84760#RTC%20SET%20TIME%20TO%20CPU%20TIME.ino

## Attiny85

![Attiny85 pinout](./images/attiny85_pinout.jpeg)