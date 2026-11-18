void FindDivDiff5Coeff1(double a, double b, double c, struct zm_kompleksno_stevilo *k) {
    double delta_x = (a - b) / (c - b);
    double delta_y = (a - c) / (c - b);
    double delta_z = (b - c) / (c - b);

    k->realna_del = delta_x * delta_x * delta_y * delta_y;
    k->imaginarna_del = delta_x * (1.0 + 2.0 * delta_x * delta_y);
    k->modul = delta_z * delta_z * delta_x * delta_x;
    k->argument = delta_z * (1.0 + 2.0 * delta_z * delta_x);
    k->konjugirano_realna_del = delta_z * delta_z * delta_y * delta_y;
    k->konjugirano_imaginarna_del = delta_y * (1.0 + 2.0 * delta_y * delta_z);
}