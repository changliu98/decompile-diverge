void table_norm(double *table1, int size1, double *table2, int size2, long *counts, int size3) {
    for (int i = 0; i < size2; i++) {
        for (int j = 0; j < size1; j++) {
            if (table1[j] > table2[i]) {
                counts[j]++;
            }
        }
    }
    
    for (int i = 0; i < size3; i++) {
        if (counts[i] == 0) {
            counts[i] = 1;
        }
    }
}