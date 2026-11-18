/**
 * dpaa_set_bits - Set specific bits in a value
 * @mask: Bitmask indicating which bits to set
 * @p: Pointer to the value to modify
 *
 * Sets the bits specified by @mask in the value pointed to by @p.
 */
void dpaa_set_bits(unsigned_long bit_mask, unsigned_long *value_ptr)
{
    *value_ptr |= bit_mask;
}