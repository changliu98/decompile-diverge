int reassemble_21(int input_value)
{
  // Extract bit 20, shift it to position 0
  // (as21 & 0x100000U) isolates bit 20, then >> 0x14 (20) moves it to bit 0
  // Cast to int to ensure signed arithmetic if needed, though result is positive here
  int bit20_extracted = (int)(input_value & 0x100000U) >> 0x14;

  // Extract bits 17-24, shift them down by 8 positions
  // (as21 & 0xffe00U) isolates bits 9-24, but specifically bits 17-24 are non-zero in this mask context
  // >> 8 moves bits 17-24 to positions 9-16
  int bits17_24_extracted = (int)(input_value & 0xffe00U) >> 8;

  // Extract bits 7-8, shift them up by 7 positions
  // (as21 & 0x180U) isolates bits 7 and 8
  // << 7 moves bit 7 to position 14 and bit 8 to position 15
  int bits7_8_extracted = (input_value & 0x180U) << 7;

  // Extract bits 6-10, shift them up by 14 positions (0xe = 14)
  // (as21 & 0x7cU) isolates bits 6-10
  // << 14 moves bit 6 to position 20, bit 7 to 21, ..., bit 10 to 24
  int bits6_10_extracted = (input_value & 0x7cU) << 0xe;

  // Extract bits 0-1, shift them up by 12 positions (0xc = 12)
  // (as21 & 3U) isolates bits 0 and 1
  // << 12 moves bit 0 to position 12 and bit 1 to position 13
  int bits0_1_extracted = (input_value & 3U) << 0xc;

  // Combine all parts using bitwise OR
  return bit20_extracted | bits17_24_extracted | bits7_8_extracted | bits6_10_extracted | bits0_1_extracted;
}