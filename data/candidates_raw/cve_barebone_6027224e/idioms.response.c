void do_line(int left, int round, int amount, int call_changed_bytes)
{
  int sw; int count; int i; int newpos;
  sw = get_sw(curbuf);
  count = get_line_count();
  if (round) {
    i = count / sw;
    if (count % sw && left)
      amount--;
    if (left)
      i -= amount;
    else
      i += amount;
    newpos = i * sw;
  }
  else {
    if (left)
      newpos = count - amount * sw;
    else
      newpos = count + amount * sw;
    if (newpos < 0)
      newpos = 0;
  }
  if (State & (1 << (10)))
    line_to(1, newpos, 0, 0, call_changed_bytes);
  else
    line_to_end(newpos, call_changed_bytes);
}