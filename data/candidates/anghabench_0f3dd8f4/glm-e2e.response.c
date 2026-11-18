const char *cros_ec_usb_power_type_string(int type) {
    const char *s;
    switch (type) {
        case 0:
            s = "USB Type C"; // 0x202c
            break;
        case 1:
            s = "USB PD"; // 0x203e
            break;
        case 2:
            s = "Proprietary"; // 0x204e
            break;
        case 3:
            s = "Type C (5V)"; // 0x2067
            break;
        case 4:
            s = "Type C (9V)"; // 0x2076
            break;
        case 5:
            s = "Type C (15V)"; // 0x208c
            break;
        case 6:
            s = "Type C (20V)"; // 0x20a2
            break;
        case 7:
            s = "Type C (60W)"; // 0x20b8
            break;
        case 8:
            s = "Type C (100W)"; // 0x20cb
            break;
        case 9:
            s = "Unknown"; // 0x20dd
            break;
        default:
            s = "Unknown"; // 0x20dd
            break;
    }
    return s;
}