void __cdecl ZVdotU22(int n, double *y0, double *y1, double *x0, double *x1, double *sums)
{
    Complex *result = (Complex *)sums;
    
    // Initialize the 2x2 result matrix to zero
    Complex r00 = {0.0, 0.0};
    Complex r01 = {0.0, 0.0};
    Complex r10 = {0.0, 0.0};
    Complex r11 = {0.0, 0.0};

    // Iterate over 'n' complex elements
    for (int i = 0; i < n; ++i)
    {
        // Extract complex numbers from interleaved arrays (real, imag, real, imag...)
        Complex y_row0 = {y0[2 * i], y0[2 * i + 1]};
        Complex y_row1 = {y1[2 * i], y1[2 * i + 1]};
        Complex x_row0 = {x0[2 * i], x0[2 * i + 1]};
        Complex x_row1 = {x1[2 * i], x1[2 * i + 1]};

        // Perform complex multiplication and accumulate:
        // (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
        
        // result[0][0] += y_row0 * x_row0
        r00.real += y_row0.real * x_row0.real - y_row0.imag * x_row0.imag;
        r00.imag += y_row0.real * x_row0.imag + y_row0.imag * x_row0.real;

        // result[0][1] += y_row0 * x_row1
        r01.real += y_row0.real * x_row1.real - y_row0.imag * x_row1.imag;
        r01.imag += y_row0.real * x_row1.imag + y_row0.imag * x_row1.real;

        // result[1][0] += y_row1 * x_row0
        r10.real += y_row1.real * x_row0.real - y_row1.imag * x_row0.imag;
        r10.imag += y_row1.real * x_row0.imag + y_row1.imag * x_row0.real;

        // result[1][1] += y_row1 * x_row1
        r11.real += y_row1.real * x_row1.real - y_row1.imag * x_row1.imag;
        r11.imag += y_row1.real * x_row1.imag + y_row1.imag * x_row1.real;
    }

    // Store the resulting 2x2 complex matrix back into the output array
    result[0] = r00; // sums[0], sums[1]
    result[1] = r01; // sums[2], sums[3]
    result[2] = r10; // sums[4], sums[5]
    result[3] = r11; // sums[6], sums[7]
}