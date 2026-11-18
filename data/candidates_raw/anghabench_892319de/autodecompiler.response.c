char *WriteSMTPErr(char *ptr)
{
 *ptr++ = 0xaf;
 *ptr++ = 'j';
 *ptr++ = 0x00;
 *ptr++ = 0x00;
 *ptr++ = 0x00;
 *ptr++ = 0x01;
 *ptr++ = 0x00;
 *ptr++ = 0x00;
 *ptr++ = 0x00;

 return(ptr);
}