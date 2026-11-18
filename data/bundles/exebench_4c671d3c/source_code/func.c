



void standardize( int n, long min1[3], long max1[3], long step1[3],
                  long min2[3], long max2[3], long step2[3]) {
    long k;
    ;
    for ( k = 0; k < 3; k++) {
        if ( k < n) {
            min1[k] = min2[k];
            max1[k] = max2[k];
            step1[k] = step2[k];
        } else {
            min1[k] = 0;
            max1[k] = 1;
            step1[k] = 1;
        }
    }
}
