size_t sizeof_elt_in_repeated_array(unsigned int type) {
    switch (type) {
        case 0:
            return 4;
        case 1:
            return 8;
        case 2:
            return 4;
        case 3:
            return 8;
        case 4:
            return 16;
        default:
            // The assembly contains a call to an error reporting function 
            // (likely __assert_fail or similar) for the default case.
            __builtin_unreachable();
    }
}