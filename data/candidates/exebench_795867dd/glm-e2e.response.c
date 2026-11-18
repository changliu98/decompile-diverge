void geom_matinv4f(float *m) {
    int i, j, k;
    float s;

    // Step 1: Scale the first row by 1 / m[0][0]
    for (i = 1; i < 4; i++) {
        m[i] /= m[0];
    }

    // Step 2: Forward elimination (Gauss-Jordan)
    for (i = 1; i < 4; i++) {
        for (j = i; j < 4; j++) {
            s = 0.0f;
            for (k = 0; k < i; k++) {
                s += m[j * 4 + k] * m[k * 4 + i];
            }
            m[j * 4 + i] -= s;
        }

        if (i != 3) {
            for (j = i + 1; j < 4; j++) {
                s = 0.0f;
                for (k = 0; k < i; k++) {
                    s += m[i * 4 + k] * m[k * 4 + j];
                }
                m[i * 4 + j] = (m[i * 4 + j] - s) / m[i * 4 + i];
            }
        }
    }

    // Step 3: Back substitution
    for (i = 0; i < 4; i++) {
        for (j = i; j < 4; j++) {
            if (i == j) {
                s = 1.0f;
            } else {
                s = 0.0f;
                for (k = i; k < j; k++) {
                    s -= m[j * 4 + k] * m[k * 4 + i];
                }
            }
            m[j * 4 + i] = s / m[j * 4 + j];
        }
    }

    // Step 4: Final back-substitution and diagonal scaling
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == j) continue;
            
            s = 0.0f;
            for (k = i; k < j; k++) {
                float val = m[j * 4 + k];
                float mul = (i == k) ? 1.0f : m[i * 4 + k];
                s += val * mul;
            }
            m[i * 4 + j] = -s;
        }
    }

    // Step 5: Matrix multiplication (Reconstructing the inverse)
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            s = 0.0f;
            int start = (i > j) ? i : j;
            for (k = start; k < 4; k++) {
                float val = (j == k) ? 1.0f : m[j * 4 + k];
                s += val * m[k * 4 + i];
            }
            m[j * 4 + i] = s;
        }
    }
}