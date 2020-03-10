# ArduinoPoliceCar
Robot controlled by mobile phone via bluetooth. Robot has siren and automatic headlights.

Two boards are used, Arduino Uno for controlling the DC motor and Mega for controlling any other functionality. They communicate via I2C,
the motor controlling module being the slave. The master communicates via Bluetooth with a phone, from where it receives commands, and
deals with the rest of the functionalities.
