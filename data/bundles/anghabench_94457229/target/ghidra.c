uint32_t clk_div_even_up(uint32_t a)

{
  uint32_t a_local;
  undefined4 local_c;
  
  if (a == 1) {
    local_c = 1;
  }
  else {
    local_c = a + 1 & 0xfffffffe;
  }
  return local_c;
}