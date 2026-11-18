1

double my_modf(double x, double *iptr) {
    double val = x;
    double scale = some_constant_1;
    int i = 0;
    long long truncated;

    // Scale the value down if it's too large to fit in a 64-bit integer
    while (i < 100) {
        truncated = (long long)val;
        if (val + some_constant_1 < (double)truncated || 
            (double)truncated < val - some_constant_1) {
            break;
        }
        val *= some_constant_3;  // Multiply by 0.1
        scale *= some_constant_2; // Multiply by 10.0
        i++;
    }

    if (i == 100) {
        // Failsafe: if the loop maxed out, return 0.0 for both parts
        *iptr = 0.0;
        return 0.0;
    } else if (i != 0) {
        // If the number was scaled down, recursively process the scaled value
        double temp_iptr;
        double frac = my_modf(val, &temp_iptr);
        
        // Reconstruct the integer part by scaling back up
        *iptr = (double)truncated * scale + temp_iptr;
        return frac;
    } else {
        // Base case: the number fits safely in a 64-bit integer
        *iptr = (double)truncated;
        return val - *iptr;
    }
}