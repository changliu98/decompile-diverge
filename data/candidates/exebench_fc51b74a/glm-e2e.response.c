void joga(int a, int *b, int c) {
    if (c % 2 == 0) {
        switch (a - 1) {
            case 0: b[0] = -3; break;
            case 1: b[1] = -3; break;
            case 2: b[2] = -3; break;
            case 3: b[3] = -3; break;
            case 4: b[4] = -3; break;
            case 5: b[5] = -3; break;
            case 6: b[6] = -3; break;
            case 7: b[7] = -3; break;
            case 8: b[8] = -3; break;
        }
    } else {
        switch (a - 1) {
            case 0: b[0] = -2; break;
            case 1: b[1] = -2; break;
            case 2: b[2] = -2; break;
            case 3: b[3] = -2; break;
            case 4: b[4] = -2; break;
            case 5: b[5] = -2; break;
            case 6: b[6] = -2; break;
            case 7: b[7] = -2; break;
            case 8: b[8] = -2; break;
        }
    }
}