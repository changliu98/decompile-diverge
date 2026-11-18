int __cdecl par_msquares_multi_code(int sw, int se, int ne, int nw)
{
    int next_col = 1;
    int col_sw = 0;
    int col_se;
    int col_ne;
    int col_nw;

    // Assign color/column index for the South-East corner
    if (se == sw) {
        col_se = col_sw;
    } else {
        col_se = next_col++;
    }

    // Assign color/column index for the North-East corner
    if (ne == se) {
        col_ne = col_se;
    } else if (ne == sw) {
        col_ne = col_sw;
    } else {
        col_ne = next_col++;
    }

    // Assign color/column index for the North-West corner
    if (nw == ne) {
        col_nw = col_ne;
    } else if (nw == se) {
        col_nw = col_se;
    } else if (nw == sw) {
        col_nw = col_sw;
    } else {
        col_nw = next_col;
    }

    // Pack the 4 corner indices into a single 8-bit integer (2 bits per corner)
    return (col_nw << 6) | (col_ne << 4) | (col_se << 2) | col_sw;
}