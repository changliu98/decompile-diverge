h
void stbtt__close_shape(stbtt_vertex *vertices, int *num_vertices, 
                        int was_off, int start_off, 
                        int sx, int sy, int scx, int scy, int cx, int cy) {
    // The assembly shows 'vertices' is passed in rdi, and 'num_vertices' in esi.
    // 'was_off' is in edx, 'start_off' in ecx.
    // 'sx' is in r8d, 'sy' is in r9d.
    // 'scx' and 'scy' are stack arguments at 0x10 and 0x18.
    // 'cx' and 'cy' are stack arguments at 0x20 and 0x28.

    if (start_off) {
        if (was_off) {
            stbtt__add_vertex(&vertices[(*num_vertices)++], 3, 
                              (cx + scx) >> 1, (cy + scy) >> 1, sx, sy);
        }
        stbtt__add_vertex(&vertices[(*num_vertices)++], 3, scx, scy, cx, cy);
    } else {
        if (was_off) {
            stbtt__add_vertex(&vertices[(*num_vertices)++], 3, scx, scy, sx, sy);
        } else {
            stbtt__add_vertex(&vertices[(*num_vertices)++], 2, scx, scy, 0, 0);
        }
    }
}