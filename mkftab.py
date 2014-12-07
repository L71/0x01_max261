#!/usr/bin/env python

import p2c

cpuclk=20000000 # AVR cpu clock
# sweep 20Hz->20k, values below: 40, 9
# sweep 40Hz->20k, 80, 8
# sweep 80Hz->20k, 160, 7
# sweep 160Hz->20k, 320, 6
base_f=30                # frequency (Hz) to start at
octaves=9                # no of octaves (9) 40Hz -> ~20KHz 
oct_steps=255/octaves   # steps per octave to calculate with.
                         # the lowest frequencies (20-40 Hz) are covered by
                         # continually adjusting the chips's clock/F ratio too.
extrasteps=255%octaves  # extra table entries to cover the last entries in the
                         # 256 steps table.

p=0
div_list=[]
csel_list=[]

i=0     # counter
while i <= ( oct_steps * octaves + extrasteps ) :
    # find out frequency ... 
    f=int(round(base_f*(2.0**(1.0/(oct_steps)))**i ))

    # find timer divider ... 
    # x = 20M/200*f
    x = cpuclk/2/(100*f)
    csel=0x01   # AVR clock /1.
    if x > 255 :
        x = cpuclk/2/8/(100*f)
        csel=0x02   # AVR clock /8
    if x > 255 :
         x = cpuclk/2/64/(100*f)
         csel=0x03  # AVR clock /64 
    
    div_list.append(x)
    csel_list.append(csel)
    i=i+1
    # print i,f,x,csel
    
p2c.print_c_list('uint8_t', 'divider', div_list, ' PROGMEM')
p2c.print_c_list('uint8_t', 'prescaler', csel_list, ' PROGMEM')
