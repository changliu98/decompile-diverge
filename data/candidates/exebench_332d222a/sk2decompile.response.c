static void fill_row_type_widths(int indent, int indent_2, int indent_3,
                                 int *widths) {
  widths[0] = 2 + indent + 3 * indent_2;
  widths[1] = 2 + 2 * indent;
  widths[2] = 10 + 2 * indent;
  widths[3] = 0;
  widths[4] = 2 + indent + indent_3;
  widths[5] = 0;
  widths[6] = 10 + 2 * indent + indent_3;
  widths[7] = 0;
  widths[8] = 4 + indent;
  widths[9] = 4;
  widths[10] = 2 + indent + indent_3;
  widths[11] = 4 + indent_3;
  widths[12] = 4 + indent_3;
}