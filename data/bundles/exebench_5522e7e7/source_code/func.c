#include <string.h>

void cenitPolarCrypt(char *str)
{
    char *from = "CENITcenitPOLARpolar";
    char *to = "POLARpolarCENITcenit";

    for (int strIndex = 0; '\0' != str[strIndex]; ++strIndex) {
        for (int letterIndex = 0; '\0' != from[letterIndex]; ++letterIndex) {
            if (str[strIndex] == from[letterIndex]) {
                str[strIndex] = to[letterIndex];
                break;
            }
        }
    }
}
