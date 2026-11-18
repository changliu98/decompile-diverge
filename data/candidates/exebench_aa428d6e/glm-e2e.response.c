void ZVdotC32(int n, double *v1, double *v2, double *v3, 
              double *w1, double *w2, double *w3, double *out) 
{
    double _Complex result[3][3] = {{0}};

    for (int i = 0, j = 1, k = 0; k < n; i++, j += 2, k += 2) {
        double a1_re = v1[k];
        double a1_im = v1[j];
        double a2_re = v2[k];
        double a2_im = v2[j];
        double a3_re = v3[k];
        double a3_im = v3[j];

        double b1_re = w1[k];
        double b1_im = w1[j];
        double b2_re = w2[k];
        double b2_im = w2[j];
        double b3_re = w3[k];
        double b3_im = w3[j];

        // result[0][0] += a1 * conj(b1)
        result[0][0] += (a1_re * b1_re + a1_im * b1_im) + I * (a1_im * b1_re - a1_re * b1_im);
        
        // result[0][1] += a1 * conj(b2)
        result[0][1] += (a1_re * b2_re + a1_im * b2_im) + I * (a1_im * b2_re - a1_re * b2_im);
        
        // result[0][2] += a1 * conj(b3)
        result[0][2] += (a1_re * b3_re + a1_im * b3_im) + I * (a1_im * b3_re - a1_re * b3_im);
        
        // result[1][0] += a2 * conj(b1)
        result[1][0] += (a2_re * b1_re + a2_im * b1_im) + I * (a2_im * b1_re - a2_re * b1_im);
        
        // result[1][1] += a2 * conj(b2)
        result[1][1] += (a2_re * b2_re + a2_im * b2_im) + I * (a2_im * b2_re - a2_re * b2_im);
        
        // result[1][2] += a2 * conj(b3)
        result[1][2] += (a2_re * b3_re + a2_im * b3_im) + I * (a2_im * b3_re - a2_re * b3_im);
        
        // result[2][0] += a3 * conj(b1)
        result[2][0] += (a3_re * b1_re + a3_im * b1_im) + I * (a3_im * b1_re - a3_re * b1_im);
        
        // result[2][1] += a3 * conj(b2)
        result[2][1] += (a3_re * b2_re + a3_im * b2_im) + I * (a3_im * b2_re - a3_re * b2_im);
        
        // result[2][2] += a3 * conj(b3)
        result[2][2] += (a3_re * b3_re + a3_im * b3_im) + I * (a3_im * b3_re - a3_re * b3_im);
    }

    // Store the 3x3 complex matrix (row-major order) into the output array
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            out[i * 6 + j * 2]     = creal(result[i][j]);
            out[i * 6 + j * 2 + 1] = cimag(result[i][j]);
        }
    }
}