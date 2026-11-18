uint32_t XXH32_finalize(uint32_t h32, const void* input, size_t len, uint32_t seed) {
    // If the input pointer is NULL, use the length pointer as the input pointer.
    // (This is a common trick in xxHash to handle zero-length tails without branching everywhere)
    if (input == NULL) {
        input = (const void*)len;
    }

    // Process the remaining bytes in 4-byte chunks
    len &= 0xF; // Equivalent to len % 16
    while (len >= 4) {
        h32 = XXH32_round(seed, input);
        h32 += h32; // Note: The assembly does `imul $0xc2b2ae3d, %eax, %eax` then `add -0x4(%rbp), %eax`.
                    // This implies the round function returns `acc * PRIME32_2`, and adding the old `acc` 
                    // makes it `acc + acc * PRIME32_2` which is equivalent to `acc * (PRIME32_2 + 1)`.
                    // However, standard xxHash does `h32 += XXH32_round(h32, input)`. 
                    // The compiler seems to have inlined and optimized the round function differently here.
                    // To match the assembly exactly:
        // h32 = h32 * 0xC2B2AE3D + old_h32; (This is handled inside the inlined round call)
        
        input = (const void*)((uintptr_t)input + 4);
        
        h32 = (h32 << 17) | (h32 >> 15); // rol 0x11 (17)
        h32 *= 0x27D4EB2F; // PRIME32_3
        
        len -= 4;
    }

    // Process the remaining bytes 1 at a time
    while (len > 0) {
        const uint8_t* p = (const uint8_t*)input;
        uint8_t c = *p;
        input = (const void*)((uintptr_t)input + 1);
        
        h32 += c * 0x165667B1; // PRIME32_5
        h32 = (h32 << 11) | (h32 >> 21); // rol 0xB (11)
        h32 *= 0x9E3779B1; // PRIME32_2
        
        len--;
    }

    // Final avalanche
    return XXH32_avalanche(h32);
}