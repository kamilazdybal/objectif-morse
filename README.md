# objectif_morse
A set of codes that acompany our Objectif Morse project.

=====================================================================
Star Log // star date 28.10.2016 // modifier: camillejr
=====================================================================

**Voici l'objectif Morse:**

We type a message on a stationary computer into the program main.cpp 
running in the terminal. 

This message is translated into Morse alphabet and the signal of dots 
and dashes is sent to the parallel port.

The parallel port's pins are connected to the small circuit with 
an LED, which blinks accordingly to the message translation.

This message is received by the phototransistor, situated in the 
close proximity of the LED.

The phototransistor pass the signal to the interpreting device, 
e.g. Arduino. 

Arduino connected to a portable computer, like a laptop, prints 
a translated message in the Arduino console.

======================================================================
Star Log // star date 08.01.2017 // modifier: camillejr
======================================================================
**Closing up the project:**

On closing up the project we tweak the codes to be more elegant and 
nicely commented.

We prepare the project description in a .pdf file.

---------------------------------------------------------------------
A plan for the future improvement:

Use a laser beam instead of a diode to transmit the signal into
larger distances. A distance of 1m or larger will be considered
a mission success.
