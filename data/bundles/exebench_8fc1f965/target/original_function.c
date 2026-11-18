void murcielagoCrypt(char *str)
{
    char *from = "MURCIELAGOmurcielago";
    char *to = "01234567890123456789";

    for (int strIndex = 0; '\0' != str[strIndex]; ++strIndex) {
        for (int letterIndex = 0; '\0' != from[letterIndex]; ++letterIndex) {
            if (str[strIndex] == from[letterIndex]) {
                str[strIndex] = to[letterIndex];
                break;
            }
        }
    }
}