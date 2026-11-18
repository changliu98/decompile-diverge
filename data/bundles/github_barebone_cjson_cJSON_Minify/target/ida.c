void __cdecl cJSON_Minify(char *json)
{
  int v1; // [rsp+Ch] [rbp-14h]
  char *into; // [rsp+10h] [rbp-10h] BYREF
  char *jsona; // [rsp+18h] [rbp-8h] BYREF

  jsona = json;
  into = json;
  if ( json )
  {
    while ( *jsona )
    {
      v1 = *jsona;
      if ( (unsigned int)(v1 - 9) < 2 || v1 == 13 || v1 == 32 )
      {
        ++jsona;
      }
      else if ( v1 == 34 )
      {
        minify_string(&jsona, &into);
      }
      else if ( v1 == 47 )
      {
        if ( jsona[1] == 47 )
        {
          skip_oneline_comment(&jsona);
        }
        else if ( jsona[1] == 42 )
        {
          skip_multiline_comment(&jsona);
        }
        else
        {
          ++jsona;
        }
      }
      else
      {
        *into++ = *jsona++;
      }
    }
    *into = 0;
  }
}