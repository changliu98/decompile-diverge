xxh_u32 XXH32_round(xxh_u32 accumulator, xxh_u32 value)
{
    // Multiply input by a prime constant and add the accumulator
    xxh_u32 mixed_value = value * -0x7a143589 + accumulator;
    // Mix bits using rotation and multiply by another prime constant
    return (mixed_value * 0x2000 | mixed_value >> 0x13) * -0x61c8864f;
}