void calcular_escala(double limite_superior, double limite_inferior, double valor, double *escala_sup, double *escala_inf) {
    double diff = limite_inferior - limite_superior;
    double temp = (limite_inferior * 2.0 - limite_superior) / 2.0;

    if (limite_superior > temp) {
        diff = limite_inferior - limite_superior;
        *escala_sup = (2.0 * limite_inferior) / diff;
        *escala_inf = limite_inferior * ((2.0 * limite_inferior + limite_superior) / diff);
    } else {
        if (limite_inferior == limite_superior) {
            *escala_sup = 1.0;
            *escala_inf = 0.0;
        } else {
            diff = limite_inferior - limite_superior;
            *escala_sup = limite_inferior / diff;
            *escala_inf = (-limite_superior * limite_inferior) / diff;
        }
    }
}