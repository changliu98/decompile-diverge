xxh_u32 XXH32_round(xxh_u32 acc,xxh_u32 input)

{
  uint uVar1;
  xxh_u32 input_local;
  xxh_u32 acc_local;
  
  uVar1 = input * -0x7a143589 + acc;
  return (uVar1 * 0x2000 | uVar1 >> 0x13) * -0x61c8864f;
}