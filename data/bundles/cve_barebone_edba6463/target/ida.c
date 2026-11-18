void __cdecl process_COM(const uchar *Data, int length)
{
  int v2; // eax
  int v3; // eax
  int a; // [rsp+8h] [rbp-3EA8h]
  int nch; // [rsp+Ch] [rbp-3EA4h]
  char Comment[16001]; // [rsp+10h] [rbp-3EA0h] BYREF
  int ch_0; // [rsp+3EA0h] [rbp-10h]
  int lengtha; // [rsp+3EA4h] [rbp-Ch]
  const uchar *Dataa; // [rsp+3EA8h] [rbp-8h]

  Dataa = Data;
  lengtha = length;
  nch = 0;
  if ( length > 16000 )
    lengtha = 16000;
  for ( a = 2; a < lengtha; ++a )
  {
    ch_0 = Dataa[a];
    if ( ch_0 != 13 || Dataa[a + 1] != 10 )
    {
      if ( ch_0 >= 32 || ch_0 == 10 || ch_0 == 9 )
      {
        v2 = nch++;
        Comment[v2] = ch_0;
      }
      else
      {
        v3 = nch++;
        Comment[v3] = 63;
      }
    }
  }
  Comment[nch] = 0;
  if ( ShowTags )
    printf("COM marker comment: %s\n", Comment);
  strcpy(ImageInfo, Comment);
}