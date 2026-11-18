int blake2b_final(blake2b_state *S, uint8_t *out, uint64_t outlen) {
    uint8_t buffer[64]; // Stack buffer at -0x60(%rbp)
    int ret;            // Stack variable at -0x4(%rbp)

    // 0x14: Zero out the 64-byte local buffer
    memset(buffer, 0, 64);

    // 0x24: Validate arguments
    if (out == NULL || outlen < S->outlen) {
        ret = -1;
        goto end;
    }

    // 0x50: Check if the last block has already been processed
    if (blake2b_is_lastblock(S) != 0) {
        ret = -1;
        goto end;
    }

    // 0x6e: Finalize the state
    blake2b_set_lastblock(S);
    blake2b_increment_counter(S, S->buflen);

    // 0x8b: Pad the remaining buffer with zeros
    memset(&S->buf[S->buflen], 0, 128 - S->buflen);

    // 0xb5: Compress the final padded block
    blake2b_compress(S, S->buf);

    // 0xc6: Serialize the 8 state words (64 bytes) into the local buffer
    for (uint64_t i = 0; i < 8; i++) { // i is stored at -0x68(%rbp)
        store64(&buffer[i], S->h[i]);
    }

    // 0x10a: Copy the requested number of bytes to the output buffer
    memcpy(out, buffer, S->outlen);

    // 0x122: Clear sensitive data from the local buffer
    memset(buffer, 0, 64);

    ret = 0;

end:
    return ret;
}