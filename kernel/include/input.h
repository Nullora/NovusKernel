#ifndef INPUT_H
#define INPUT_H
char scancode_to_ascii(unsigned char sc);
void record_keyboard_to_buffer(char* buffer, unsigned long long size);

#endif