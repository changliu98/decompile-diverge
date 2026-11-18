void stbhw__corner_process_v_rect(struct stbhw__process_v_rect_arg *arg, int x, int y, int p4, int p5, int p6, int p7, int p8, int p9, int p10) {
    int v_size = arg->field_8->field_4;
    void *output = arg->field_20;
    int stride = arg->field_28;

    // Draw clipped corners
    stbhw__draw_clipped_corner(output, stride, x + 1, y, p4 * 16 + p8, v_size, 0);
    stbhw__draw_clipped_corner(output, stride, x, y + 1, p5 * 16 + p6, v_size, 5);
    stbhw__draw_clipped_corner(output, stride, x + v_size + 1, y + 1, p9 * 16 + p10, v_size, 1);
    stbhw__draw_clipped_corner(output, stride, x, y + v_size + 1, p6 * 16 + p7, v_size, 4);
    stbhw__draw_clipped_corner(output, stride, x + v_size + 1, y + v_size + 1, p10 * 16 + p7, v_size, 5);
    stbhw__draw_clipped_corner(output, stride, x + 1, y + v_size * 2 + 1, p7 * 16 + p7, v_size, 3);

    // Draw horizontal and vertical lines based on corner type conditions
    if (arg->field_8->field_28[p4] != 0) {
        stbhw__draw_hline(output, stride, x, y, v_size, v_size * 2, 1, 1);
    }
    if (arg->field_8->field_58[p5] != 0) {
        stbhw__draw_hline(output, stride, x, y, v_size, v_size * 2, 1, v_size + 1);
    }
    if (arg->field_8->field_48[p6] != 0) {
        stbhw__draw_hline(output, stride, x, y, v_size, v_size * 2, 1, v_size * 2 + 1);
    }
    if (arg->field_8->field_38[p8] != 0) {
        stbhw__draw_hline(output, stride, x, y, v_size, v_size * 2, v_size + 1, 1);
    }
    if (arg->field_8->field_28[p9] != 0) {
        stbhw__draw_hline(output, stride, x, y, v_size, v_size * 2, v_size + 1, v_size + 1);
    }
    if (arg->field_8->field_58[p10] != 0) {
        stbhw__draw_hline(output, stride, x, y, v_size, v_size * 2, v_size + 1, v_size * 2 + 1);
    }

    // Draw vertical and horizontal edge lines
    stbhw__draw_vline(output, stride, x, y, p4 * 3, 0);
    stbhw__draw_vline(output, stride, x, y + v_size, p5 * 3 + 36, 0);
    stbhw__draw_vline(output, stride, x, y + v_size * 2 + 1, p6 * 3 + 24, 0);
    stbhw__draw_hline(output, stride, x + v_size + 1, y, p8 * 3 + 12, 0);
    stbhw__draw_hline(output, stride, x + v_size + 1, y + v_size, p9 * 3, 0);
    stbhw__draw_hline(output, stride, x + v_size + 1, y + v_size * 2 + 1, p10 * 3 + 36, 0);
}