static void shift_line(int left, int word, int count, int select) {
  int sw = get_sw_value_indent(SID_INDENT);
  int indent = get_indent();
  int n;
  if (word) {
    n = indent / sw;
    if (indent % sw && left) count--;
    if (left) {
      n -= count;
      if (n < 0) n = 0;
    } else {
      n += count;
    }
    indent = n * sw;
  } else {
    if (left) {
      indent -= count * sw;
      if (indent < 0) indent = 0;
    } else {
      indent += count * sw;
    }
  }
  if (last_flags & 0x00000200)
    change_indent(1, indent, 0, 0, select);
  else
    set_indent(indent, select ? 1 : 0);
}