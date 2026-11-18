void func0(int value, char *output_buffer)
{
    int index = 0;
    *output_buffer = '\0';
    while (0 < value) {
        for (; values[index] <= value; value -= values[index]) {
            strcat(output_buffer, representations[index]);
        }
        if (0 < value) {
            index++;
        }
    }
}