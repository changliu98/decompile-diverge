const char *ata_err_string(unsigned int err) {
    const char *err_str;

    if (err & AC_ERR_HOST_BUS) {
        err_str = "host bus error"; // 0x2004
    } else if (err & AC_ERR_ATA_BUS) {
        err_str = "ATA bus error"; // 0x2013
    } else if (err & AC_ERR_TIMEOUT) {
        err_str = "timeout"; // 0x2021
    } else if (err & AC_ERR_HSM) {
        err_str = "HSM violation"; // 0x2029
    } else if (err & AC_ERR_SYSTEM) {
        err_str = "internal error"; // 0x2037
    } else if (err & AC_ERR_MEDIA) {
        err_str = "media error"; // 0x2046
    } else if (err & AC_ERR_INVALID) {
        err_str = "invalid argument"; // 0x2052
    } else if (err & AC_ERR_DEV) {
        err_str = "device error"; // 0x2063
    } else if (err & AC_ERR_NCQ) {
        err_str = "NCQ error"; // 0x2070
    } else if (err & AC_ERR_NODEV_HINT) {
        err_str = "NRDV"; // 0x207a
    } else {
        err_str = "unknown error"; // 0x2092
    }

    return err_str;
}