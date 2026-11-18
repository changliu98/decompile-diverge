uint32_t __cdecl clk_div_even_up(uint32_t a)
{
  if ( a == 1 )
    return 1;
  else
    return (a + 1) & 0xFFFFFFFE;
}