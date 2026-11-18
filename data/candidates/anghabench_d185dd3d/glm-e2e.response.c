bool pmic_thermal_is_aux(int arg) {
    bool var_5;
    bool var_6;

    if (arg >= 4 && arg <= 64) {
        var_5 = ((arg - 4) % 12) == 0;
    } else {
        var_6 = false;
        if (arg >= 8 && arg <= 68) {
            var_6 = ((arg - 8) % 12) == 0;
        }
        var_5 = var_6;
    }

    return var_5 & 1;
}