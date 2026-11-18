int func0(int *tuple, int length)
{
    int i;
    char result;

    for (i = 0; i < length; i++) {
        if (tuple[i] == 0) {
            result = 1;
            break;
        }
    }

    return result & 1;
}