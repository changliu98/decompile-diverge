void __cdecl shift_line(int left, int round, int amount, int call_changed_bytes)
{
  int sw_val;       // Tab stop / shift width value
  int cur_indent;   // Current indentation level
  int new_indent;   // Target indentation level
  int indent_steps; // Calculated indentation in terms of shift width steps

  sw_val = get_sw_value_indent(curbuf);
  cur_indent = get_indent();

  if (round)
  {
    // Rounding mode: shift by a multiple of sw_val, aligning to the nearest step boundary.
    indent_steps = cur_indent / sw_val;

    // If currently misaligned and shifting left, an extra step is consumed to reach the boundary.
    if ((cur_indent % sw_val != 0) && left)
      --amount;

    if (left)
    {
      // Shift left, bounded to a minimum of 0
      indent_steps = indent_steps - amount;
      if (indent_steps < 0)
        indent_steps = 0;
    }
    else
    {
      // Shift right
      indent_steps = indent_steps + amount;
    }
    new_indent = sw_val * indent_steps;
  }
  else
  {
    // Non-rounding mode: shift strictly by amount * sw_val
    if (left)
    {
      new_indent = cur_indent - amount * sw_val;
      if (new_indent < 0)
        new_indent = 0;
    }
    else
    {
      new_indent = cur_indent + amount * sw_val;
    }
  }

  // Apply the new indentation based on the global State flags
  if (IS_STATE_FLAG_SET(State, 0x200))
  {
    change_indent(1, new_indent, 0, 0, call_changed_bytes);
  }
  else
  {
    set_indent(new_indent, call_changed_bytes != 0);
  }
}