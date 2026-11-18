double blue_filter(double white, double *buf)
{
    // Filter coefficients
    const double b0 = 0.5362;
    const double b1 = 0.115926;
    
    const double a0 = 0.0555179;
    const double a1 = 0.0750759;
    const double a2 = 0.153852;
    const double a3 = 0.3104856;
    const double a4 = 0.5329522;
    const double a5 = -0.016898;
    
    const double c0 = 0.99886;
    const double c1 = 0.99332;
    const double c2 = 0.969;
    const double c3 = 0.8665;
    const double c4 = 0.55;
    const double c5 = 0.7616;

    // Update filter states
    buf[0] = white * a0 - c0 * buf[0];
    buf[1] = white * a1 - c1 * buf[1];
    buf[2] = white * a2 - c2 * buf[2];
    buf[3] = white * a3 - c3 * buf[3];
    buf[4] = white * a4 - c4 * buf[4];
    buf[5] = white * a5 + c5 * buf[5];

    // Calculate blue output
    double blue = white * b0 + buf[0] + buf[1] + buf[2] + buf[3] + buf[4] + buf[5] + buf[6];
    
    // Update the last state for the next iteration
    buf[6] = white * b1;

    return 0.11 * blue;
}