int wifirate2_ratetbl_inx(unsigned char rate) {
    int inx = 0;
    rate &= 0x7F;
    
    // The jump table handles values from 2 to 0x6C (108)
    if (rate >= 2 && rate <= 0x6C) {
        switch (rate) {
            case 0x02: inx = 0; break;
            case 0x04: inx = 1; break;
            case 0x0B: inx = 2; break;
            case 0x0C: inx = 3; break;
            case 0x12: inx = 4; break;
            case 0x16: inx = 5; break;
            case 0x18: inx = 6; break;
            case 0x24: inx = 7; break;
            case 0x2C: inx = 8; break;
            case 0x30: inx = 9; break;
            case 0x48: inx = 10; break;
            case 0x60: inx = 11; break;
            default: break;
        }
    }
    
    return inx;
}