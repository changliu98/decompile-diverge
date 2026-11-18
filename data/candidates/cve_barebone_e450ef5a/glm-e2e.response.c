void adjust_skipcol(void) {
    int off1;
    int off2;
    int so_ff;
    int width1;
    int width2;
    int scrolled;
    int loops;
    int leftcol;
    long so;

    // Check initial conditions to see if adjustment is needed
    if (curwin->field_0 == 0 || curwin->field_4 == 0 || curwin->field_8 != (void*)curwin->field_18) {
        return;
    }

    off1 = curwin->field_24 - curwin_col_off();
    width1 = off1;
    width2 = width1 + curwin_col_off2();

    so = get_scrolloff_value();
    if (so == 0) {
        so_ff = 0;
    } else {
        so_ff = off1 + (so - 1) * width2;
    }

    validate_cheight();

    // Check if line fits in the window
    if (curwin->field_28 == curwin->field_20) {
        if (plines_win(curwin, curwin->field_8, 0) <= curwin->field_20) {
            reset_skipcol();
            return;
        }
    }

    do {
        validate_virtcol();
        
        int cond = 0;
        if (curwin->field_30 > 0) {
            cond = (curwin->field_2c < curwin->field_30 + 3 + so_ff);
        }

        if (!cond) {
            break;
        }

        if (curwin->field_30 >= off1 + width2) {
            curwin->field_30 -= width2;
        } else {
            curwin->field_30 -= off1;
        }

        redraw_later(0x28);
        scrolled = 1;
        validate_virtcol();
    } while (1);

    if (scrolled) {
        return;
    }

    leftcol = curwin->field_2c - curwin->field_30 + so_ff;
    loops = 0;

    if (leftcol >= off1) {
        leftcol -= off1;
        loops++;
    }

    if (leftcol > width2) {
        loops += leftcol / width2;
        leftcol %= width2;
    }

    if (loops < curwin->field_20) {
        return;
    }

    if (curwin->field_30 == 0) {
        curwin->field_30 += off1;
        loops--;
    }

    if (loops >= curwin->field_20) {
        curwin->field_30 += (loops - curwin->field_20) * width2;
    }

    redraw_later(0x28);
}