int func0(double T, double rh, double p) {
    return (int)(611.2 * exp((17.67 * rh) / (rh + 243.5)) + 32.0 * p / T);
}