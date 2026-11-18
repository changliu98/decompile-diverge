void edosk2674_smsc_outw(unsigned short value, volatile unsigned short *addr) {
    unsigned short swapped = (value >> 8) | (value << 8);
    *addr = swapped;
}