unsigned short qla24xx_calc_ct_iocbs(unsigned short dsd) {
    unsigned short iocbs = 1;
    
    if (dsd > 2) {
        iocbs += (dsd - 2) / 5;
        if ((dsd - 2) % 5 != 0) {
            iocbs += 1;
        }
    }
    
    return iocbs;
}