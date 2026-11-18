int is_midi_message(unsigned char *data)
{
    if (data[0] == 0x7f ||
        (data[0] == 0x88 && (data[1] == 0x07 || data[1] == 0x08 ||
        ((data[1] & 0xf0) == 0xb0 || ((data[1] & 0xf0) == 0xc0))))
    )
        return 1;
    return 0;
}