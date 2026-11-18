// Sets the nth bit of the integer pointed to by ptr to 1
// and returns the updated value.
int set_bit(int *target_value, int bit_position)
{
    // Create a mask with the nth bit set by shifting 1 left by n positions.
    // Apply bitwise AND with 0x1f to ensure the shift amount is within 0-31 range.
    // Use bitwise OR to set the nth bit of *ptr to 1 without affecting other bits.
    *target_value = *target_value | 1 << ((byte)bit_position & 0x1f);
    // Return the updated value of the integer.
    return *target_value;
}