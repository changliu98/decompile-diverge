static inline U32 XXH32_round(U32 acc, U32 val) {
  val *= 2048144777;
  val = (((val) << (13)) | ((val) >> (32 - (13))));
  acc ^= val;
  acc = (((acc) << (16)) | ((acc) >> (32 - (16))));
  acc *= 2654435761U;
  return acc;
}