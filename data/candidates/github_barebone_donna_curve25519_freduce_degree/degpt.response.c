void freduce_degree(limb *result)
{
  // Reduce degree by folding high-order limbs into lower-order limbs
  // using the relation x^13 = 1 (or similar field reduction)
  // Each high limb at index i+10 is multiplied by 13 and added to limb at index i
  
  // Fold limb at index 0x12 (18) into limb at index 8
  result[8] = result[0x12] * 13 + result[8];
  // Fold limb at index 0x11 (17) into limb at index 7
  result[7] = result[0x11] * 13 + result[7];
  // Fold limb at index 0x10 (16) into limb at index 6
  result[6] = result[0x10] * 13 + result[6];
  // Fold limb at index 0xf (15) into limb at index 5
  result[5] = result[0xf] * 13 + result[5];
  // Fold limb at index 0xe (14) into limb at index 4
  result[4] = result[0xe] * 13 + result[4];
  // Fold limb at index 0xd (13) into limb at index 3
  result[3] = result[0xd] * 13 + result[3];
  // Fold limb at index 0xc (12) into limb at index 2
  result[2] = result[0xc] * 13 + result[2];
  // Fold limb at index 0xb (11) into limb at index 1
  result[1] = result[0xb] * 13 + result[1];
  // Fold limb at index 10 into limb at index 0 (output[0])
  *result = result[10] * 13 + *result;
}