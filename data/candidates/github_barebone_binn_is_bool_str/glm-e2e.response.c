bool is_bool_str(const char *str, int *out_val) {
    if (str == NULL || out_val == NULL) {
        return false;
    }

    // Check for explicit true strings
    if (strcasecmp(str, "true") == 0 || 
        strcasecmp(str, "yes") == 0 || 
        strcasecmp(str, "on") == 0) 
    {
        *out_val = 1;
        return true;
    }

    // Check for explicit false strings
    if (strcasecmp(str, "false") == 0 || 
        strcasecmp(str, "no") == 0 || 
        strcasecmp(str, "off") == 0) 
    {
        *out_val = 0;
        return true;
    }

    // Check for integer representation
    if (is_integer(str)) {
        long long val = atoi64(str);
        *out_val = (val != 0) ? 1 : 0;
        return true;
    }

    // Check for float representation
    if (is_float(str)) {
        double val = atof(str);
        // The assembly uses `ucomisd` and checks parity (NaN) and zero flags,
        // which corresponds to checking if the value is not equal to 0.0.
        *out_val = (val != 0.0) ? 1 : 0;
        return true;
    }

    return false;
}