bool isLegalUTF8(const unsigned __int8 *source, int length)
{
    const unsigned __int8 *srcptr = &source[length];
    unsigned __int8 byte1, byte2, byte3;

    switch (length)
    {
        case 1:
            return (*source >= 0x80u && *source < 0xC2u) ? false : (*source <= 0xF4u);

        case 4:
            srcptr--;
            byte3 = source[length - 1];
            if (byte3 < 0x80u || byte3 > 0xBFu)
                return false;
            /* fallthrough */

        case 3:
            byte2 = *(srcptr - 1);
            srcptr--;
            if (byte2 < 0x80u || byte2 > 0xBFu)
                return false;
            /* fallthrough */

        case 2:
            byte1 = *(srcptr - 1);
            if (byte1 > 0xBFu)
                return false;

            switch (*source)
            {
                case 0xE0: // 224
                    if (byte1 < 0xA0u) return false;
                    break;
                case 0xF0: // 240
                    if (byte1 < 0x90u) return false;
                    break;
                case 0xF4: // 244
                    if (byte1 > 0x8Fu) return false;
                    break;
                default:
                    if (byte1 < 0x80u) return false;
                    break;
            }

            return (*source >= 0x80u && *source < 0xC2u) ? false : (*source <= 0xF4u);

        default:
            return false;
    }
}