void fill_row_type_widths(int a, int b, int c, struct RowWidths *out) {
    out->width0 = a + 2 + b * 3;
    out->width1 = a * 2 + 2;
    out->width2 = a * 2 + 10;
    out->width3 = 0;
    out->width4 = a + 2 + c;
    out->width5 = 0;
    out->width6 = a + 10 + c;
    out->width7 = 0;
    out->width8 = a + 4;
    out->width9 = 4;
    out->width10 = a + 2 + c;
    out->width11 = c + 4;
    out->width12 = c + 4;
}