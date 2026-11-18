unsigned int getExtendTest(unsigned char arg) {
    unsigned int val = arg;
    unsigned short res;

    if (val > 15) {
        res = 0;
    } else {
        switch (val) {
            case 0:
                res = 0;
                break;
            case 1:
                res = 1;
                break;
            case 2:
                res = 2;
                break;
            case 3:
                res = 4;
                break;
            case 4:
                res = 8;
                break;
            case 5:
                res = 16;
                break;
            case 6:
                res = 32;
                break;
            case 7:
                res = 64;
                break;
            case 8:
                res = 128;
                break;
            case 9:
                res = 256;
                break;
            case 10:
                res = 512;
                break;
            case 11:
                res = 1024;
                break;
            case 12:
                res = 2048;
                break;
            case 13:
                res = 4096;
                break;
            case 14:
                res = 8192;
                break;
            case 15:
                res = 16384;
                break;
        }
    }
    return res;
}