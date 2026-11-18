/*
 * put_user_quad - Copy a 64-bit value to user space.
 * @val: The 64-bit value to copy.
 * @addr: Pointer to the user-space address where the value will be written.
 *
 * This function writes the 64-bit value @val to the user-space address
 * specified by @addr. It assumes that the address is valid and accessible
 * from user space.
 */
void put_user_quad(unsigned long value, long *user_addr)
{
    /* Write the 64-bit value to the user-space address */
    *user_addr = value;
}