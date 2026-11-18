static void fill_row_type_widths(int x, int y, int cx, RECT *r)
{
    r->left = x * 3 + 2;
    r->top = y * 2 + 2;
    r->right = r->left + cx * 2;
    r->bottom = r->top + 2;
    r->bottom += 4;
}