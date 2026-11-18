uint16_t getExtendTest(uint8_t i)
{
    uint16_t result;

    switch (i)
    {
        case 0:
            result = 0x0000;
            break;
        case 1:
            result = 0x0001;
            break;
        case 2:
            result = 0x0002;
            break;
        case 3:
            result = 0x0004;
            break;
        case 4:
            result = 0x0008;
            break;
        case 5:
            result = 0x0010;
            break;
        case 6:
            result = 0x0020;
            break;
        case 7:
            result = 0x0040;
            break;
        case 8:
            result = 0x0080;
            break;
        case 9:
            result = 0x0100;
            break;
        case 10:
            result = 0x0200;
            break;
        case 11:
            result = 0x0400;
            break;
        case 12:
            result = 0x0800;
            break;
        case 13:
            result = 0x1000;
            break;
        case 14:
            result = 0x2000;
            break;
        case 15:
            result = 0x4000;
            break;
        default:
            result = 0x0000;
            break;
    }

    return result;
}