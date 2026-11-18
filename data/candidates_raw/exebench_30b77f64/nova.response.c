void func0(double altitude, double *temperature, double *pressure) {
    *pressure = e_0 * pow(gama, altitude / L);
    *temperature = T_0 * pow(1 + (gama - 1) * e_0 / (R * T_0) * altitude,
                             gama / (R * T_0) * e_0);
}