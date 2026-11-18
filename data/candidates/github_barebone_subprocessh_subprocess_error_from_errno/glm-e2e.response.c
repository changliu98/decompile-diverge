int subprocess_error_from_errno(int err) {
    int ret;

    // err == 1 (EPERM)
    if (err == 1) {
        ret = -5;
    } 
    // err == 2 (ENOENT)
    else if (err == 2) {
        ret = -4;
    } 
    // err == 12 (ENOMEM)
    else if (err == 12) {
        ret = -6;
    } 
    // err == 13 (EACCES)
    else if (err == 13) {
        ret = -5;
    } 
    // err == 20 (ENOTDIR)
    else if (err == 20) {
        ret = -4;
    } 
    // err == 23, 24, or 25 (ENFILE, EMFILE, ENOTTY)
    // (err + 23 == 0 is equivalent to err == -23, but since err is positive errno, 
    // this checks if err - 23 is in the range [0, 2])
    else if (err >= 23 && err <= 25) {
        ret = -6;
    } 
    // Any other errno
    else {
        ret = -1;
    }

    return ret;
}