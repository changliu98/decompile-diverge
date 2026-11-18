unsigned char maya_pb_route_shift(int arg) {
    static unsigned char shift[10] = { /* 10 bytes of data initialized in .rodata */ };
    return shift[arg % 10];
}