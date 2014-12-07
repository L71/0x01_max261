0x01_max261
===========

This Maxim Max261 based Eurorack filter module is making this filter IC useful
for audio processing in a standard 16HP Eurorack synth module. 
The IC is a dual filter and each filter is independently controlled using front
panel knobs and control voltage inputs. The filter mode selection buttons provide
these filter types in each filter section:
Low pass, Band pass, High pass, Notch (Lowpass+Bandpass mixed).
The maximum frequency range is logarithmic 30Hz-16.6KHz with the current firmware.

There are separate knobs and CV inputs for the frequency and resonance of each filter.
The resulting control voltages are read by an Atmel ATmega328 microcontroller that
is i turn programming the max261 filter IC. It also provides the clock signals to
the filter sections. 

The output of filter A is connected to the input of filter B if no cables are inserted.

The filter IC used is not built for use in musical instruments. It suffers from some
clock signal bleed (+- 4mV at 50x the filter cutoff frequency) and due to its switched
capacitor technology it behaves somewhat like a sampled system and has a Nyquist
frequency at 25x the filter cutoff frequency. The clock bleed will be audible in LP
mode with low cutoff values if the filter is the last unit in the signal chain.
Make sure to read the Maxim max261 data sheets if you plan to build one of these. 


The microcontroller source code is released under the GPL v3.0 license. 
The PCBs and front panel drawings are released under the Creative Commons CC BY-SA 4.0 license.

