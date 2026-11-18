void OPL3_ChannelWriteC0(struct IMAGE *image, uint8_t byte) {
    image->memory[7] = (byte & 0x0E) >> 1;
    image->memory[8] = (byte & 0x01);
    update_out(image);
    if (image->memory[100] == 0) {
        image->memory[7] = 0xFFFF;
        image->memory[8] = 0xFFFF;
        image->memory[9] = 0;
        image->memory[10] = 0;
    } else {
        image->memory[9] = (byte & 0x20)? 0xFFFF : 0;
        image->memory[10] = (byte & 0x40)? 0xFFFF : 0;
        image->memory[11] = (byte & 0x80)? 0xFFFF : 0;
        image->memory[12] = (byte & 0x100)? 0xFFFF : 0;
    }
}