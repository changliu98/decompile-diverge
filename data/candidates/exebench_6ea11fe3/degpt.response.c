/**
 * sync_set_bit - Atomically set a bit in memory
 * @nr: Bit number to set
 * @addr: Address of the memory block containing the bit
 *
 * This function sets the specified bit in the memory location pointed to by addr.
 * It uses LOCK/UNLOCK macros to ensure atomicity of the operation.
 * The bit is calculated by adding (nr >> 3) to the address to find the byte,
 * and then setting the bit within that byte using (nr & 7).
 */
void sync_set_bit(int bit_number, unsigned_long *memory_address)
{
    LOCK();
    // Calculate the byte address by adding (nr / 8) to the base address
    // Set the specific bit within that byte using a bitmask
    *(byte *)((long)memory_address + ((long)bit_number >> 3)) |= '\x01' << (bit_number & 7U);
    UNLOCK();
}