int __cdecl blake2b_final(blake2b_state *S, void *out, size_t outlen)
{
    uint8_t buffer[64];
    size_t i;

    memset(buffer, 0, sizeof(buffer));

    if (!out || outlen < S->outlen)
        return -1;

    if (blake2b_is_lastblock(S))
        return -1;

    blake2b_increment_counter(S, S->buflen);
    blake2b_set_lastblock(S);
    
    // Zero-pad the remaining buffer
    memset(&S->buf[S->buflen], 0, 128 - S->buflen);
    blake2b_compress(S, S->buf);

    // Serialize the state hash into the buffer
    for (i = 0; i < 8; ++i)
        store64(&buffer[8 * i], S->h[i]);

    // Copy the result to the output
    memcpy(out, buffer, S->outlen);

    // Securely wipe the local buffer
    secure_zero_memory(buffer, sizeof(buffer));

    return 0;
}