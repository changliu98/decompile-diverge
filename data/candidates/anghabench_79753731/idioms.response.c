static _Bool check_attr_len(unsigned int attr_len, unsigned int expected_len)
{
    _Bool valid = 1;
    if (attr_len != expected_len) {
        if (expected_len == OVS_ATTR_NESTED) {
            valid = 1;
        } else if (expected_len == OVS_ATTR_VARIABLE) {
            valid = 1;
        } else {
            valid = 0;
        }
    }
    return valid;
}