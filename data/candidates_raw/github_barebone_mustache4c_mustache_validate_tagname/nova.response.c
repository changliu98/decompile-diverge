int func0(char *line, size_t len, int is_dir) {
    int ret;
    size_t i;

    if (is_dir == 1 && line[0] == '.') {
        ret = 0;
    } else if (line[0]!= '.' && line[len - 1] == '.') {
        ret = -1;
    } else {
        for (i = 0; i < len; i++) {
            if (line[i] =='' || line[i] == '\t' || line[i] == '\n' ||
                line[i] == '\v' || line[i] == '\f' || line[i] == '\r') {
                ret = -1;
                break;
            } else if (line[i] == '.' && i + 1 < len && line[i + 1] == '.') {
                ret = -1;
                break;
            }
        }
    }

    return ret;
}