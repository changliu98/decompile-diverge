// Adds the value 'val' to the unsigned long integer pointed to by 'p'
void load_and_store(unsigned_long *ptr, unsigned_long value)
{
    // Update the value at the memory location pointed to by 'p'
    *ptr += value;
}