Optimized and annotated for reverse engineering
void __cdecl set_page_data(int potval, char *buf)
{
    // Cast the 1-byte char pointer to a 4-byte DWORD pointer 
    // and write the 32-bit integer value directly to the buffer.
    *(int *)buf = potval;
}