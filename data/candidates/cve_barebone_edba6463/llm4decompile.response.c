void process_COM(unsigned char *Data, int length)
{
    int a, ch;
    char Comment[16000 +1];
    int nch = 0;

    if (length > 16000) length = 16000;
    for (a=2; a<length; a++) {
        ch = Data[a];
        if (ch == 0x0D && Data[a+1] == 0x0A) continue;
        if (ch < 0x20 && ch != 0x0A && ch != 0x09) ch = '?';
        Comment[nch++] = ch;
    }
    Comment[nch] = 0;
    if (ShowTags) printf("COM marker comment: %s\n", Comment);
    strcpy(ImageInfo.Comments, Comment);
}