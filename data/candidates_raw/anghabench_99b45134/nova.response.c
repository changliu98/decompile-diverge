void func0(char c, char *s, char *v) {
    unsigned long j = c;

    switch (j) {
    case 0x61:
        *s = table_61[0];
        *v = table_61[1];
        break;
    case 0x62:
        *s = table_62[0];
        *v = table_62[1];
        break;
    case 0x63:
        *s = table_63[0];
        *v = table_63[1];
        break;
    case 0x64:
        *s = table_64[0];
        *v = table_64[1];
        break;
    case 0x65:
        *s = table_65[0];
        *v = table_65[1];
        break;
    case 0x66:
        *s = table_66[0];
        *v = table_66[1];
        break;
    case 0x67:
        *s = table_67[0];
        *v = table_67[1];
        break;
    case 0x68:
        *s = table_68[0];
        *v = table_68[1];
        break;
    case 0x69:
        *s = table_69[0];
        *v = table_69[1];
        break;
    default:
        *s = 0;
        *v = 0;
    }
}