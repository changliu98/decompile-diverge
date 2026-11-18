static int editorSyntaxToColor(int n) {
    size_t n_mod_6 = n % 6;
    int ret;

    switch (n_mod_6) {
    case 0:
        ret = 36;
        break;
    case 1:
        ret = 33;
        break;
    case 2:
        ret = 32;
        break;
    case 3:
        ret = 35;
        break;
    case 4:
        ret = 31;
        break;
    case 5:
        ret = 34;
        break;
    default:
        ret = 37;
        break;
    }

    return ret;
}