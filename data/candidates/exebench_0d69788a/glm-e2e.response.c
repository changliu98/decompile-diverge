int tens(int *val) {
    int count = 0;
    int v = *val;
    int t = v / 10;

    if (t <= 9) {
        switch (t) {
            case 0: count = 6; break;
            case 1: count = 6; break;
            case 2: count = 7; break;
            case 3: count = 5; break;
            case 4: count = 5; break;
            case 5: count = 5; break;
            case 6: count = 6; break;
            case 7: count = 6; break;
            case 8: count = 6; break;
            case 9: count = 6; break;
        }
        
        int u = v - 10;
        if (u <= 9) {
            switch (u) {
                case 0: count = 8; break;
                case 1: count = 8; break;
                case 2: count = 9; break;
                case 3: count = 7; break;
                case 4: count = 7; break;
                case 5: count = 8; break;
                case 6: count = 8; break;
                case 7: count = 6; break;
                case 8: count = 6; break;
                case 9: count = 3; break;
            }
            *val = 0;
            return count;
        } else {
            return 0;
        }
    } else {
        *val = v % 10;
        return count;
    }
}