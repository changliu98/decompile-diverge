double estLog(double x) {
    double val = 1.0;
    double el = 1.0;
    int i = 1;
    while (1) {
        if (x > el) {
            val += el;
            el *= P;
            i++;
        } else {
            break;
        }
    }
    return val;
}