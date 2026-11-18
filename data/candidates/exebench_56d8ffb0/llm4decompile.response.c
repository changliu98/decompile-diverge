void wdc_UtilsDeleteCharFromString(char *buffer, int buffSize, char charToRemove)
{
    int i, j;

    if (buffer && buffSize) {
        for (i=0, j=0; i<buffSize && buffer[i]; i++) {
            if (buffer[i] != charToRemove) {
                buffer[j++] = buffer[i];
            }
        }
        buffer[j] = '\0';
    }
}