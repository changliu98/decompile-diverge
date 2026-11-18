unsigned char
pop(unsigned char stack[100], int* position)
{
    unsigned char result = 0xff;

    if (*position < 100 && *position >= 0) {
        result = stack[*position];
        *position -= 1;
    }

    return result;
}