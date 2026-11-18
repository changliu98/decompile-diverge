void __cdecl shift_line(int left, int round, int amount, int call_changed_bytes)
{
  int sw_val; // [rsp+0h] [rbp-20h]
  int i; // [rsp+8h] [rbp-18h]
  int ia; // [rsp+8h] [rbp-18h]
  int count; // [rsp+Ch] [rbp-14h]
  int counta; // [rsp+Ch] [rbp-14h]

  sw_val = get_sw_value_indent(curbuf);
  count = get_indent();
  if ( round )
  {
    i = count / sw_val;
    if ( count % sw_val && left )
      --amount;
    if ( left )
    {
      ia = i - amount;
      if ( ia < 0 )
        ia = 0;
    }
    else
    {
      ia = i + amount;
    }
    counta = sw_val * ia;
  }
  else if ( left )
  {
    counta = count - amount * sw_val;
    if ( counta < 0 )
      counta = 0;
  }
  else
  {
    counta = count + amount * sw_val;
  }
  if ( (State & 0x200) != 0 )
    change_indent(1, counta, 0, 0, call_changed_bytes);
  else
    set_indent(counta, call_changed_bytes != 0);
}