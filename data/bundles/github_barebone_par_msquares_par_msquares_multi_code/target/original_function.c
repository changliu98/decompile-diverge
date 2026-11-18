static int par_msquares_multi_code(int sw, int se, int ne, int nw)
{
    int code[4];
    int ncols = 0;
    code[0] = ncols++;
    if (se == sw) {
        code[1] = code[0];
    } else {
        code[1] = ncols++;
    }
    if (ne == se) {
        code[2] = code[1];
    } else if (ne == sw) {
        code[2] = code[0];
    } else {
        code[2] = ncols++;
    }
    if (nw == ne) {
        code[3] = code[2];
    } else if (nw == se) {
        code[3] = code[1];
    } else if (nw == sw) {
        code[3] = code[0];
    } else {
        code[3] = ncols++;
    }
    return code[0] | (code[1] << 2) | (code[2] << 4) | (code[3] << 6);
}