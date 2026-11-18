void shift_line(int is_left, int is_normal_mode, int count, int arg4) {
    int sw_value = get_sw_value_indent(curbuf);
    int indent = get_indent();
    int new_indent = indent;

    if (is_normal_mode != 0) {
        int num_indents = indent / sw_value;
        int remainder = indent % sw_value;

        if (remainder != 0 && is_left != 0) {
            count--;
        }

        if (is_left != 0) {
            num_indents -= count;
            if (num_indents < 0) {
                num_indents = 0;
            }
        } else {
            num_indents += count;
        }
        new_indent = num_indents * sw_value;
    } else {
        if (is_left != 0) {
            new_indent -= sw_value * count;
            if (new_indent < 0) {
                new_indent = 0;
            }
        } else {
            new_indent += sw_value * count;
        }
    }

    if ((State & 0x200) != 0) {
        change_indent(1, new_indent, 0, arg4);
    } else {
        set_indent(new_indent, arg4 != 0 ? 1 : 0);
    }
}