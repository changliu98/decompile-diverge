static xxh_u32 XXH32_round(xxh_u32 acc, xxh_u32 input)
{
    acc += input * XXH_PRIME32_2;
    acc  = XXH_rotl32(acc, 13);
    acc *= XXH_PRIME32_1;
#if (defined(__SSE4_1__) || defined(__aarch64__) || defined(__wasm_simd128__)) && !defined(XXH_ENABLE_AUTOVECTORIZE)
    /*
     * UGLY HACK:
     * A compiler fence is used to prevent GCC and Clang from
     * autovectorizing the XXH32 loop (pragmas and attributes don't work for some
     * reason) without globally disabling SSE4.1.
     *
     * The reason we want to avoid vectorization is because despite working on
     * 4 integers at a time, there are multiple factors slowing XXH32 down on
     * SSE4:
     * - There's a ridiculous amount of lag from pmulld (10 cycles of latency on
     *   newer chips!) making it slightly slower to multiply four integers at
     *   once compared to four integers independently. Even when pmulld was
     *   fastest, Sandy/Ivy Bridge, it is still not worth it to go into SSE
     *   just to multiply unless doing a long operation.
     *
     * - Four instructions are required to rotate,
     *      movqda tmp,  v // not required with VEX encoding
     *      pslld  tmp, 13 // tmp <<= 13
     *      psrld  v,   19 // x >>= 19
     *      por    v,  tmp // x |= tmp
     *   compared to one for scalar:
     *      roll   v, 13    // reliably fast across the board
     *      shldl  v, v, 13 // Sandy Bridge and later prefer this for some reason
     *
     * - Instruction level parallelism is actually more beneficial here because
     *   the SIMD actually serializes this operation: While v1 is rotating, v2
     *   can load data, while v3 can multiply. SSE forces them to operate
     *   together.
     *
     * This is also enabled on AArch64, as Clang is *very aggressive* in vectorizing
     * the loop. NEON is only faster on the A53, and with the newer cores, it is less
     * than half the speed.
     *
     * Additionally, this is used on WASM SIMD128 because it JITs to the same
     * SIMD instructions and has the same issue.
     */
    XXH_COMPILER_GUARD(acc);
#endif
    return acc;
}