xxh_u32 __cdecl XXH32_round(xxh_u32 acc, xxh_u32 input)
{
  const xxh_u32 PRIME32_1 = 2654435761u;
  const xxh_u32 PRIME32_2 = 2246822519u;

  acc += input * PRIME32_2;
  acc = __ROL4__(acc, 13);
  acc *= PRIME32_1;
  
  return acc;
}