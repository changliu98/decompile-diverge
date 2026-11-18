void heaviside(double *input, double *end, double *output) {
    *output = 0.0;
    int length = ((end - input) >> 3) + 1;
    
    for (int i = 0; i < length; i++) {
        char condition = 0;
        if (*output == 0.0) {
            condition = (input[i] >= 0.0);
        }
        
        *output = (condition & 1) ? 1.0 : 0.0;
    }
}