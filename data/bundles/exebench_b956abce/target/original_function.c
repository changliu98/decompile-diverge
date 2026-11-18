static void set_page_data(int potval, char *buf)
{
 unsigned int word, *wordp;
 int len, blen;

 wordp = (unsigned int *)buf;
 word = potval;
 wordp[0] = word;

}