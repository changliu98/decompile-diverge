int set_filename(char *to_name, char *from_name)
{
    int result;

    while (*from_name != 0) {
        if (*from_name == '/') {
            *to_name = 0;
            result = 2;
            break;
        } else {
            *to_name = *from_name;
            to_name++;
            from_name++;
            result = 1;
        }
    }

    if (*from_name == 0) {
        *to_name = 0;
        result = 1;
    }

    return result;
}