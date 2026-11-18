int i2s_sf_mclkdiv(int div, unsigned int *reg) {
    if (div >= 1 && div <= 14) {
        switch (div) {
            case 1:
                *reg |= 0x14000000;
                break;
            case 2:
                *reg |= 0x13000000;
                break;
            case 3:
                *reg |= 0x12000000;
                break;
            case 4:
                *reg |= 0x0E000000;
                break;
            default:
                // For div = 5 to 14, it falls through to the default case
                // which calculates the register value dynamically.
                *reg |= ((div - 1) << 24) & 0x1F000000;
                break;
        }
        return 0;
    } else {
        if (div % 2 != 0) {
            return -1;
        }
        
        int val = (div / 2) - 1;
        if (val == 20 || val == 19 || val == 18 || val == 14) {
            return -1;
        }
        
        *reg |= ((div / 2 - 1) << 24) & 0x1F000000;
        return 0;
    }
}