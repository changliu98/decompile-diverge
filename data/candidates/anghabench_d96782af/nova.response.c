double rapl_dram_energy_units_probe(int reg, double val) {
    double tmp;
    switch (reg) {
    case 15:
    case 14:
    case 13:
    case 12:
    case 11:
    case 10:
    case 9:
    case 8:
    case 7:
    case 6:
    case 5:
    case 4:
    case 3:
    case 2:
    case 1:
    case 0:
        tmp = val;
        break;
    default:
        tmp = val;
        break;
    }
    return tmp;
}