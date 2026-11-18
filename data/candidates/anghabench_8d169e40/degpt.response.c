/**
 * @brief Test command for FSP invert operation.
 *
 * @param reg_val The register value to process.
 * @return The inverted register value if it matches specific patterns, otherwise the original value.
 */
uchar fsp_test_invert_cmd(uchar register_value)
{
    // Check if the register value matches specific predefined patterns
    if (register_value == 0xe9 || register_value == 0xee || register_value == 0xf2 || register_value == 0xff) {
        // Invert the bits of the register value using XOR with 0xff
        return register_value ^ 0xff;
    }
    // Return the original register value if no pattern matches
    return register_value;
}