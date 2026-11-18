void ecryptfs_get_versions(int *rows, int *cols, int *style)
{
    *rows = LINES;
    *cols = COLS;
    if (style)
        *style = cur_win->style;
}