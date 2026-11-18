void SaltTextAway(struct xterm *t, int which, struct cell *start, struct cell *end)
{
    struct tscreen *screen = &t->screen;
    struct selected_cells *scp;
    int i; int eol; int need;
    struct cell tmp;
    char *line; char *lp;
    tmp = *start;
    if (which >= 0 && which < (int)(sizeof(screen->selected_cells)/sizeof((screen->selected_cells)[0])))
    {
        scp = &screen->selected_cells[which];
        if (tmp.row == end->row && tmp.col < end->col)
        {
            i = tmp.col;
            tmp.col = end->col;
            end->col = i;
        }
        end->col--;
        if (tmp.row == end->row)
        {
            need = xterm_get_line_length(screen, tmp.row, tmp.col, end->col);
        }
        else
        {
            need = xterm_get_line_length(screen, tmp.row, tmp.col, screen->max_col);
            for (i = tmp.row + 1; i < end->row; i++)
            {
                need += xterm_get_line_length(screen, i, 0, screen->max_col) + 1;
            }
            if (end->col >= 0)
            {
                need += xterm_get_line_length(screen, end->row, 0, end->col);
            }
        }
        if (screen->wide_chars)
        {
            need *= 4;
        }
        if (need < 0)
        {
            return;
        }
        if (need + 1 > scp->data_limit)
        {
            line = xterm_realloc(need + 1);
            if (line == ((void *)0))
            {
                xterm_error(71);
            }
            xterm_free(scp->data_buffer);
            scp->data_buffer = line;
            scp->data_limit = need + 1;
        }
        else
        {
            line = scp->data_buffer;
        }
        if (line == ((void *)0))
        {
            return;
        }
        line[need] = '\0';
        if (end->row == tmp.row)
        {
            lp = xterm_get_line(screen, end->row, tmp.col, end->col, line, &eol);
        }
        else
        {
            lp = xterm_get_line(screen, tmp.row, tmp.col, screen->max_col, line, &eol);
            if (eol)
            {
                lp++;
                *lp++ = '\n';
            }
            for (i = tmp.row + 1; i < end->row; i++)
            {
                lp = xterm_get_line(screen, i, 0, screen->max_col, lp, &eol);
                if (eol)
                {
                    lp++;
                    *lp++ = '\n';
                }
            }
            if (end->col >= 0)
            {
                lp = xterm_get_line(screen, end->row, 0, end->col, lp, &eol);
            }
        }
        *lp = '\0';
        scp->data_length = lp - line;
    }
}