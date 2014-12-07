// max261 command & control (header file)

#ifndef _MAX261_

#define _MAX261_

void init_max261(void);

void set_mode(uint8_t, uint8_t);

void max261_write_f(uint8_t, uint8_t);
void max261_write_q(uint8_t, uint8_t);

#endif 

