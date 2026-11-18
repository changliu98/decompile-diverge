void xmlrpc_char_encode(char *outbuffer,char *s1)

{
  byte bVar1;
  _func_void_mowgli_string__ptr_char_ptr_size_t *p_Var2;
  mowgli_string_t *pmVar3;
  size_t sVar4;
  mowgli_string_t *s;
  char buf2 [15];
  uchar c;
  unsigned_long i;
  char *s1_local;
  char *outbuffer_local;
  
  pmVar3 = mowgli_string_create();
  buf2[0] = '\0';
  *outbuffer = '\0';
  if ((s1 != (char *)0x0) && (*s1 != '\0')) {
    for (i = 0; s1[i] != '\0'; i = i + 1) {
      bVar1 = s1[i];
      if (bVar1 < 0x80) {
        if (bVar1 == 0x26) {
          (*pmVar3->append)(pmVar3,"&amp;",5);
        }
        else if (bVar1 == 0x3c) {
          (*pmVar3->append)(pmVar3,"&lt;",4);
        }
        else if (bVar1 == 0x3e) {
          (*pmVar3->append)(pmVar3,"&gt;",4);
        }
        else if (bVar1 == 0x22) {
          (*pmVar3->append)(pmVar3,"&quot;",6);
        }
        else {
          (*pmVar3->append_char)(pmVar3,bVar1);
        }
      }
      else {
        snprintf(buf2,0xf,"&#%d;",(ulong)bVar1);
        p_Var2 = pmVar3->append;
        sVar4 = strlen(buf2);
        (*p_Var2)(pmVar3,buf2,sVar4);
      }
    }
    memcpy(outbuffer,pmVar3->str,0x1000);
  }
  return;
}