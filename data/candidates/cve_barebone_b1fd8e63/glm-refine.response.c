void __cdecl gitn_box_del(GF_Box *s)
{
    if (s)
    {
        // s[1].type is located at offset 0x8 (assuming 8-byte GF_Box header).
        // LOWORD() extracts the lower 16 bits, representing a 16-bit count.
        u32 count = LOWORD(s[1].type);
        
        // s[1].size is located at offset 0x10 and acts as a pointer to an array of pointers.
        void **array = (void **)s[1].size;

        for (u32 i = 0; i < count; ++i)
        {
            // Each element in the array is an 8-byte pointer.
            // The original expression `16LL * i + s[1].size + 8` is equivalent to `array + i`.
            if (array[i])
            {
                gf_free(array[i]);
            }
        }

        // Free the array itself if it was allocated.
        if (array)
        {
            gf_free(array);
        }

        // Finally, free the main structure.
        gf_free(s);
    }
}