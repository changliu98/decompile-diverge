static void GetCOMmarker(unsigned char * Data, int Length)
{
    int a, b;
    char Comment[16000];

    b = 0;

    if (Length > 16000) Length = 16000;

    for (a=2;a<Length;a++){
        if (Data[a] == 0x0d && Data[a+1] == 0x0a) continue;
        if ((Data[a] >= 32 || Data[a] == 0x0a || Data[a] == 0x09))
            Comment[b++] = Data[a];
        else
            Comment[b++] = '?';
    }
    Comment[b] = 0;

    if (ShowTags) printf("COM marker comment: %s\n", Comment);

    strcpy(ImageInfo.Comments, Comment);
}