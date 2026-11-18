// Copies 20 integers (0x14 bytes) from src to dst
void copy_poly(int *destination, int *source)
{
    for (int index = 0; index < 0x14; index++) {
        destination[index] = source[index];
    }
}