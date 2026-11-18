int dv_write_ssyb_id(uint8_t subsystem_number, uint8_t frame_rate, uint8_t *buffer)
{
    // Set the first byte based on the subsystem number (syb_num)
    if (subsystem_number == 0 || subsystem_number == 6) {
        // For syb_num 0 or 6, set the frame rate (fr) in the upper 7 bits and 0xf in the lower 4 bits
        *buffer = frame_rate << 7 | 0xf;
    } else if (subsystem_number == 11) {
        // For syb_num 11, set the frame rate (fr) in the upper 7 bits and 0x7f in the lower 7 bits
        *buffer = frame_rate << 7 | 0x7f;
    } else {
        // For other syb_num values, set the frame rate (fr) in the upper 7 bits and 0xf in the lower 4 bits
        *buffer = frame_rate << 7 | 0xf;
    }
    // Set the second byte with the subsystem number (syb_num) in the lower 4 bits and 0xf0 in the upper 4 bits
    buffer[1] = subsystem_number & 0xf | 0xf0;
    // Set the third byte to 0xff
    buffer[2] = 0xff;
    // Return the number of bytes written
    return 3;
}