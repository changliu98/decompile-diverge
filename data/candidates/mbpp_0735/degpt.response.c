int func0(int num)
{
  // Base case: if n is 1, return 1
  if (num == 1) {
    return 1;
  }
  else {
    // Otherwise, XOR n with the result of set_middle_bits(n)
    // This effectively toggles the middle bits of n as determined by set_middle_bits
    return num ^ set_middle_bits(num);
  }
}