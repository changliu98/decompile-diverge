bool check_attr_len(uint actual_len, uint expected_len)
{
    // If the expected length does not match the actual length and is not a nested attribute,
    // return true only if the expected length indicates a variable-length attribute.
    if (expected_len != attr_len && expected_len != OVS_ATTR_NESTED) {
        return expected_len == OVS_ATTR_VARIABLE;
    }
    // Otherwise, the length check passes.
    return true;
}