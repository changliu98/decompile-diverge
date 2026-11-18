int subprocess_error_from_errno(int errorCode)
{
    // Map specific error codes (1, 0xd) to -5
    if (errorCode == 1 || errorCode == 0xd) {
        return -5;
    }
    // Map specific error codes (2, 0x14) to -4
    if (errorCode == 2 || errorCode == 0x14) {
        return -4;
    }
    // Map specific error code (0xc) to -6
    if (errorCode == 0xc) {
        return -6;
    }
    // Map non-zero error codes in range [1, 0x17] to -6
    if (errorCode != 0 && errorCode <= 0x17) {
        return -6;
    }
    // Default return value for unmapped or out-of-range errors
    return -1;
}