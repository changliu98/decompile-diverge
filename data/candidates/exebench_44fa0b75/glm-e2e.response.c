void calculate_proportions(int total, int part, int *out1, int *out2) {
    int val1 = 0;
    if (out1 != 0) {
        val1 = *out1;
    }
    
    int val2 = 0;
    if (out2 != 0) {
        val2 = *out2;
    }
    
    if (total > 0 && part >= total) {
        if (val1 > 0 || val2 <= 0) {
            val2 = (part * val1) / total;
        } else {
            val1 = (total * val2) / part;
        }
    } else {
        if (part > 0) {
            val1 = (total * val2) / part;
        }
    }
    
    if (out1 != 0) {
        *out1 = val1;
    }
    
    if (out2 != 0) {
        *out2 = val2;
    }
}