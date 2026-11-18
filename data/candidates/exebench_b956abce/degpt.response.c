// Sets the integer value at the beginning of the buffer to potval.
// Note: This assumes buf is properly aligned for an int and has sufficient space.
void set_page_data(int page_value, char *buffer)
{
    // Cast the char pointer to an int pointer and assign the value
    *(int *)buffer = page_value;
}