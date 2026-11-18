const char* selectOpName(int op) {
    const char* name;
    switch (op) {
        case 0x80:
            name = "Add"; // Assuming string at 0x200e
            break;
        case 0x81:
            name = "Sub"; // Assuming string at 0x2018
            break;
        case 0x82:
            name = "Mul"; // Assuming string at 0x2004
            break;
        default:
            name = "Unknown"; // Assuming string at 0x201f
            break;
    }
    return name;
}