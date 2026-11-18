int __cdecl type_family(int type)
{
    // 0x00
    if (type == 0)
        return 241;

    // 0x20-0x21, 0x40-0x41, 0x60-0x61, 0x80-0x81
    if ((type & 0x1F) == 0 && (type & 0xFE) != 0)
        return 242;

    // 0x62, 0xA6-0xA7
    if (type == 98 || (unsigned int)(type - 166) < 2)
        return 243;

    // 0x82, 0xA0-0xA5, 0xA8-0xA9, 0xB001-0xB005
    if (type == 130 || (unsigned int)(type - 160) < 10 || (unsigned int)(type - 45057) < 5)
        return 244;

    // 0xC0, 0xD001-0xD004
    if (type == 192 || (unsigned int)(type - 53249) < 4)
        return 245;

    // 0xE0-0xE2
    if ((unsigned int)(type - 224) < 3)
        return 247;

    // 0x80001
    if (type == 524385)
        return 246;

    return 0;
}