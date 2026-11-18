int type_family(int arg) {
    int result;
    
    switch (arg) {
        case 0:
            result = 0xf1;
            break;
        case 0x20:
        case 0x21:
            result = 0xf2;
            break;
        case 0x40:
        case 0x41:
            result = 0xf2;
            break;
        case 0x60:
        case 0x61:
            result = 0xf2;
            break;
        case 0x62:
            result = 0xf3;
            break;
        case 0x80:
        case 0x81:
            result = 0xf2;
            break;
        case 0x82:
            result = 0xf3;
            break;
        case 0x83:
            result = 0xf4;
            break;
        case 0xa0:
            result = 0xf4;
            break;
        case 0xa1:
        case 0xa2:
        case 0xa3:
        case 0xa4:
            result = 0xf4;
            break;
        case 0xa6:
        case 0xa7:
            result = 0xf3;
            break;
        case 0xc0:
            result = 0xf5;
            break;
        case 0xe0:
        case 0xe1:
        case 0xe2:
            result = 0xf7;
            break;
        case 0xb000:
        case 0xb001:
        case 0xb002:
        case 0xb003:
        case 0xb004:
        case 0xb005:
            result = 0xf4;
            break;
        case 0xd000:
        case 0xd001:
        case 0xd002:
        case 0xd003:
        case 0xd004:
            result = 0xf5;
            break;
        case 0x80061:
            result = 0xf6;
            break;
        default:
            result = 0;
            break;
    }
    
    return result;
}