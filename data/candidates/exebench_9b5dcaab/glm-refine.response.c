void __cdecl modify_calculated_address_new_syntax(int *foo)
{
  // Increment the 2nd integer (offset +4 bytes) by 5
  foo[1] += 5;
  
  // Decrement the 3rd integer (offset +8 bytes) by 5
  foo[2] -= 5;
}