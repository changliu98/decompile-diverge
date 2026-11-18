static const char *func0(const char *name, int len) {
    const char *type;
    if (strncmp(name, "EV_", 3) == 0 || strncmp(name, "IN_", 3) == 0 || strncmp(name, "BTN_", 4) == 0) {
        type = "EV_KEY";
    } else if (strncmp(name, "REL_", 4) == 0 || strncmp(name, "ABS_", 4) == 0 || strncmp(name, "SW_", 3) == 0) {
        type = "EV_REL";
    } else if (strncmp(name, "LED_", 4) == 0 || strncmp(name, "SND_", 4) == 0) {
        type = "EV_LED";
    } else if (strncmp(name, "FF_", 3) == 0 && len >= 20) {
        type = "EV_FF";
    } else if (strncmp(name, "SW_", 3) == 0 && len >= 21) {
        type = "EV_SW";
    } else if (strncmp(name, "Msc_", 4) == 0 || strncmp(name, "SW_", 3) == 0) {
        type = "EV_MSC";
    } else if (strncmp(name, "PWR_", 4) == 0) {
        type = "EV_PWR";
    } else {
        type = "EV_CNT";
    }
    return type;
}