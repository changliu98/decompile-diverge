float ran2(long *idum) {
    int j;
    long k;
    float temp;

    if (*idum <= 0) {
        if (-(*idum) < 1) {
            *idum = 1;
        } else {
            *idum = -(*idum);
        }
        idum2 = *idum;
        
        for (j = 39; j >= 0; j--) {
            k = *idum / 53668;
            *idum = 40014 * (*idum - k * 53668) - 12211 * k;
            if (*idum < 0) {
                *idum += 2147483563;
            }
            if (j < 32) {
                iv[j] = *idum;
            }
        }
        iy = iv[0];
    }

    k = *idum / 53668;
    *idum = 40014 * (*idum - k * 53668) - 12211 * k;
    if (*idum < 0) {
        *idum += 2147483563;
    }

    k = idum2 / 52774;
    idum2 = 40692 * (idum2 - k * 52774) - 3791 * k;
    if (idum2 < 0) {
        idum2 += 2147483399;
    }

    j = iy / 67108862;
    iy = iv[j] - idum2;
    iv[j] = *idum;

    if (iy < 1) {
        iy += 2147483562;
    }

    temp = (float)(1.0 / 2147483563.0) * (float)iy;
    
    if (temp > 1.0) {
        return 1.0;
    } else {
        return temp;
    }
}