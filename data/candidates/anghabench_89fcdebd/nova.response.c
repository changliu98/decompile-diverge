unsigned short qla24xx_calc_ct_iocbs(unsigned short n) {
    unsigned short i = 1;
    if (n > 2) {
        i += (n - 2) / 5;
        if ((n - 2) % 5!= 0)
            i++;
    }
    return i;
}