int
get_type_and_count2(unsigned char c, unsigned char *type, unsigned char *count)
{
    unsigned char ret;

    if (c < 128) {
        *type = 0;
        *count = c;
        ret = 1;
    } else if (c < 144) {
        *type = 1;
        *count = c - 128;
        ret = 1;
    } else if (c < 160) {
        *type = 2;
        *count = c - 144;
        ret = 1;
    } else if (c < 192) {
        *type = 3;
        *count = c - 160;
        ret = 1;
    } else if (c >= 224) {
        *type = 34;
        *count = c - 224;
        ret = 1;
    } else {
        switch (c) {
        case 192:
            *type = 4;
            *count = 0;
            ret = 1;
            break;
        case 194:
            *type = 5;
            *count = 0;
            ret = 1;
            break;
        case 195:
            *type = 5;
            *count = 0;
            ret = 1;
            break;
        case 196:
            *type = 6;
            *count = 0;
            ret = 1;
            break;
        case 197:
            *type = 7;
            *count = 0;
            ret = 1;
            break;
        case 198:
            *type = 8;
            *count = 0;
            ret = 1;
            break;
        case 199:
            *type = 9;
            *count = 0;
            ret = 1;
            break;
        case 200:
            *type = 10;
            *count = 0;
            ret = 1;
            break;
        case 201:
            *type = 11;
            *count = 0;
            ret = 1;
            break;
        case 202:
            *type = 12;
            *count = 0;
            ret = 1;
            break;
        case 203:
            *type = 13;
            *count = 0;
            ret = 1;
            break;
        case 204:
            *type = 14;
            *count = 0;
            ret = 1;
            break;
        case 205:
            *type = 15;
            *count = 0;
            ret = 1;
            break;
        case 206:
            *type = 16;
            *count = 0;
            ret = 1;
            break;
        case 207:
            *type = 17;
            *count = 0;
            ret = 1;
            break;
        case 208:
            *type = 18;
            *count = 0;
            ret = 1;
            break;
        case 209:
            *type = 19;
            *count = 0;
            ret = 1;
            break;
        case 210:
            *type = 20;
            *count = 0;
            ret = 1;
            break;
        case 211:
            *type = 21;
            *count = 0;
            ret = 1;
            break;
        case 212:
            *type = 22;
            *count = 0;
            ret = 1;
            break;
        case 213:
            *type = 23;
            *count = 0;
            ret = 1;
            break;
        case 214:
            *type = 24;
            *count = 0;
            ret = 1;
            break;
        case 215:
            *type = 25;
            *count = 0;
            ret = 1;
            break;
        case 216:
            *type = 26;
            *count = 0;
            ret = 1;
            break;
        case 217:
            *type = 27;
            *count = 0;
            ret = 1;
            break;
        case 218:
            *type = 28;
            *count = 0;
            ret = 1;
            break;
        case 219:
            *type = 29;
            *count = 0;
            ret = 1;
            break;
        case 220:
            *type = 30;
            *count = 0;
            ret = 1;
            break;
        case 221:
            *type = 31;
            *count = 0;
            ret = 1;
            break;
        case 222:
            *type = 32;
            *count = 0;
            ret = 1;
            break;
        case 223:
            *type = 33;
            *count = 0;
            ret = 1;
            break;
        default:
            ret = 0;
        }
    }

    return ((ret & 1) ? 1 : 0);
}