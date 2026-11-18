char *gf_text_get_utf8_line(char *szLine, u32 lineSize, FILE *txt_in, s32 unicode_type)
{
    char *szLineReturn;
    memset(szLine, 0, lineSize);

    szLineReturn = gf_fgets(szLine, lineSize, txt_in);
    if (szLineReturn==NULL) return NULL;

    if (unicode_type==0 || unicode_type==1)
    {
        u32 i, j;
        char szLineConv[2048];
        for (i=0, j=0; i<strlen(szLine); i++)
        {
            if (unicode_type==0 && (szLine[i]&0x80))
            {
                if ((szLine[i+1]&0xC0)==0x80)
                {
                    if ((szLine[i]&0xE0)==0xC0)
                    {
                        szLineConv[j++] = szLine[i++];
                    }
                    else if ((szLine[i]&0xF0)==0xE0)
                    {
                        szLineConv[j++] = szLine[i++];
                        szLineConv[j++] = szLine[i++];
                    }
                    else if ((szLine[i]&0xF8)==0xF0)
                    {
                        szLineConv[j++] = szLine[i++];
                        szLineConv[j++] = szLine[i++];
                        szLineConv[j++] = szLine[i++];
                    }
                    else
                    {
                        i++;
                    }
                }
                else
                {
                    szLineConv[j++] = 0xC0 | ((szLine[i]>>6)&0x03);
                    szLine[i] &= 0xBF;
                }
            }
            szLineConv[j++] = szLine[i];
            if (j>=2048 -1) break;
        }
        szLineConv[j] = 0;
        strcpy(szLine, szLineConv);
    }
    else
    {
        if (unicode_type==2)
        {
            u32 i;
            for (i=0; szLine[i] || szLine[i+1]; i+=2)
            {
                char c;
                c = szLine[i];
                szLine[i] = szLine[i+1];
                szLine[i+1] = c;
            }
        }

        {
            u32 i;
            char szLineConv[2048];
            wchar_t *wstr = (wchar_t*)szLine;
            i = gf_utf8_wcstombs(szLineConv, 2048, &wstr);
            if (i==-1) i=0;
            szLineConv[i] = 0;
            strcpy(szLine, szLineConv);
        }

        if (unicode_type==3)
        {
            gf_fgetc(txt_in);
        }
    }
    return szLineReturn;
}