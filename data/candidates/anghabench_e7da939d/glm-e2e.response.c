const char* test_to_str(int arg) {
    const char* result;
    switch (arg) {
        case 0x80:
            result = "String 2"; // 0x200c
            break;
        case 0x81:
            result = "String 1"; // 0x2004
            break;
        default:
            result = "String 3"; // 0x2015
            break;
    }
    return result;
}