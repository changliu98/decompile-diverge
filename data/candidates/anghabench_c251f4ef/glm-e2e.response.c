const char *hcfs2string(int hcfs) {
    const char *result;
    switch (hcfs) {
        case 128:
            result = "HCFS_UNSEATED"; // 0x2014
            break;
        case 129:
            result = "HCFS_SEATED";   // 0x201a
            break;
        case 130:
            result = "HCFS_READY";    // 0x2021
            break;
        case 131:
            result = "HCFS_ACTIVE";   // 0x202d
            break;
        default:
            result = "HCFS_UNKNOWN";  // 0x2035
            break;
    }
    return result;
}