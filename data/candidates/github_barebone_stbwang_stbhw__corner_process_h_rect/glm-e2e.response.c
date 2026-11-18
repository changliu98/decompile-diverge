void stbhw__corner_process_h_rect(
    struct stbhw__rect *rect,
    int x,
    int y,
    int corner_tl,
    int corner_tr,
    int corner_bl,
    int corner_br
) {
    int size = rect->field_0x8->field_0x4;

    // Top-Left Corner
    stbhw__draw_clipped_corner(
        rect,
        rect->field_0x20,
        rect->field_0x28,
        x + 1,
        y,
        stbhw__corner_types[corner_tl][corner_tr],
        size,
        2
    );

    // Top-Right Corner
    stbhw__draw_clipped_corner(
        rect,
        rect->field_0x20,
        rect->field_0x28,
        x + size + 1,
        y,
        stbhw__corner_types[corner_tr][corner_br],
        size,
        3
    );

    // Bottom-Left Corner
    stbhw__draw_clipped_corner(
        rect,
        rect->field_0x20,
        rect->field_0x28,
        x,
        y + 1,
        stbhw__corner_types[corner_tl][corner_bl],
        size,
        1
    );

    // Bottom-Right Corner
    stbhw__draw_clipped_corner(
        rect,
        rect->field_0x20,
        rect->field_0x28,
        x + size * 2 + 1,
        y + 1,
        stbhw__corner_types[corner_bl][corner_br],
        size,
        4
    );

    // Bottom-Left Inner Corner
    stbhw__draw_clipped_corner(
        rect,
        rect->field_0x20,
        rect->field_0x28,
        x + 1,
        y + size + 1,
        stbhw__corner_types[corner_bl][corner_tl],
        size,
        0
    );

    // Bottom-Right Inner Corner
    stbhw__draw_clipped_corner(
        rect,
        rect->field_0x20,
        rect->field_0x28,
        x + size + 1,
        y + size + 1,
        stbhw__corner_types[corner_br][corner_tr],
        size,
        2
    );

    // Conditional pixel drawing based on corner types
    if (rect->field_0x8->field_0x38[corner_tl] != 0) {
        stbhw__draw_pixel(rect, rect->field_0x20, rect->field_0x28, x, y, size * 2, size, 1, 1);
    }

    if (rect->field_0x8->field_0x48[corner_tr] != 0) {
        stbhw__draw_pixel(rect, rect->field_0x20, rect->field_0x28, x, y, size * 2, size, size + 1, 1);
    }

    if (rect->field_0x8->field_0x58[corner_br] != 0) {
        stbhw__draw_pixel(rect, rect->field_0x20, rect->field_0x28, x, y, size * 2, size, size * 2 + 1, 1);
    }

    if (rect->field_0x8->field_0x28[corner_bl] != 0) {
        stbhw__draw_pixel(rect, rect->field_0x20, rect->field_0x28, x, y, size * 2, size, 1, size + 1);
    }

    if (rect->field_0x8->field_0x38[corner_bl] != 0) {
        stbhw__draw_pixel(rect, rect->field_0x20, rect->field_0x28, x, y, size * 2, size, size + 1, size + 1);
    }

    if (rect->field_0x8->field_0x48[corner_br] != 0) {
        stbhw__draw_pixel(rect, rect->field_0x20, rect->field_0x28, x, y, size * 2, size, size * 2 + 1, size + 1);
    }

    // Horizontal and Vertical Edge Lines
    stbhw__draw_hline(rect, rect->field_0x20, rect->field_0x28, x, y, &stbhw__edge_types[corner_tl][0]);
    stbhw__draw_hline(rect, rect->field_0x20, rect->field_0x28, x + size, y, &stbhw__edge_types[corner_tr][1]);
    stbhw__draw_hline(rect, rect->field_0x20, rect->field_0x28, x + size * 2 + 1, y, &stbhw__edge_types[corner_br][2]);
    stbhw__draw_hline(rect, rect->field_0x20, rect->field_0x28, x, y + size + 1, &stbhw__edge_types[corner_bl][0]);

    stbhw__draw_vline(rect, rect->field_0x20, rect->field_0x28, x + size, y, &stbhw__edge_types[corner_bl][1]);
    stbhw__draw_vline(rect, rect->field_0x20, rect->field_0x28, x + size * 2 + 1, y + size + 1, &stbhw__edge_types[corner_br][2]);
}