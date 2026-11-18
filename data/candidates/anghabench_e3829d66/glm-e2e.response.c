double blue_filter(double *arr, double param) {
    // The constants are represented as placeholders since their exact 
    // floating-point values are read from memory addresses (e.g., 0x2078).
    // The XOR operation with 0x8000000000000000 flips the sign bit of the double.
    
    arr[0] = (param * C_2070) - (arr[0] * C_2078);
    arr[1] = (param * C_2060) - (arr[1] * C_2068);
    arr[2] = (param * C_2050) - (arr[2] * C_2058);
    arr[3] = (param * C_2040) - (arr[3] * C_2048);
    arr[4] = (param * C_2030) - (arr[4] * C_2038);
    arr[5] = (param * C_2020) - (arr[5] * C_2028);
    
    double sum = arr[0] + arr[1] + arr[2] + arr[3] + arr[4] + arr[5] + arr[6];
    double temp = sum + (param * C_2018);
    
    arr[6] = param * C_2010;
    
    return temp * C_2008;
}