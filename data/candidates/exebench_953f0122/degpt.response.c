// Initializes the MurmurHash3 context by setting the expected digest length to 16 bytes (128 bits).
// Parameters:
//   ret_digest_len: Pointer to an integer that will be set to the size of the hash output in bytes.
// Returns:
//   0 on success.
int murmur3_init_hash(uint *digest_length)
{
    // Set the output digest length to 16 bytes (128 bits), which is the standard size for MurmurHash3_32.
    *digest_length = 0x10;
    return 0;
}