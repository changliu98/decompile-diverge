// Clears the bit at the specified index in the storage array
// by masking it with the inverse of the bit position.
void RewindBitPosition(size_t target_bit_index, size_t *current_storage_index, uint8_t *bit_array)
{
    // Calculate the byte index by shifting right by 3 (dividing by 8)
    // and clear the specific bit within that byte using bitwise AND with the inverted mask.
    bit_array[target_bit_index >> 3] &= (uint8_t)(~(1U << (target_bit_index & 7)));
    
    // Update the current storage index to the new position.
    *current_storage_index = target_bit_index;
}