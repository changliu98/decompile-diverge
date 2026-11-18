int stbhw__change_color(int old_color, int num_options, int *weights)
{
    int i; int total; int choice;
    if (!weights)
        return (old_color + ((int)stbhw__getticks() / 16 % (num_options - 1)) + 1) % num_options;
    total = 0;
    for (i = 0; i < num_options; i++)
        if (i != old_color)
            total += weights[i];
    choice = (int)stbhw__getticks() / 16 % total;
    total = 0;
    for (i = 0; i < num_options; i++)
        if (i != old_color) {
            total += weights[i];
            if (total > choice)
                break;
        }
    ((void) sizeof ((i < num_options) ? 1 : 0), __extension__ ({ if (i < num_options) ; else __assert_fail ("k < num_options", "func.c", 697, __extension__ __PRETTY_FUNCTION__); }));
    return i;
}