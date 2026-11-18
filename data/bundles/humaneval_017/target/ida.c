int *__cdecl func0(const char *music_string, int *count)
{
  int v2; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v7; // [rsp+4h] [rbp-4Ch]
  int v8; // [rsp+8h] [rbp-48h]
  int v9; // [rsp+Ch] [rbp-44h]
  size_t len; // [rsp+10h] [rbp-40h]
  int i; // [rsp+1Ch] [rbp-34h]
  char *temp_music_string; // [rsp+20h] [rbp-30h]
  int music_string_length; // [rsp+28h] [rbp-28h]
  char current[3]; // [rsp+2Dh] [rbp-23h] BYREF
  int capacity; // [rsp+30h] [rbp-20h]
  int size; // [rsp+34h] [rbp-1Ch]
  int *out; // [rsp+38h] [rbp-18h]
  int *counta; // [rsp+40h] [rbp-10h]
  const char *music_stringa; // [rsp+48h] [rbp-8h]

  music_stringa = music_string;
  counta = count;
  out = 0LL;
  size = 0;
  capacity = 0;
  memset(current, 0, sizeof(current));
  v2 = strlen(music_stringa);
  music_string_length = v2 + 1;
  temp_music_string = (char *)malloc(v2 + 2);
  strcpy(temp_music_string, music_stringa);
  strcat(temp_music_string, " ");
  for ( i = 0; i < music_string_length; ++i )
  {
    if ( temp_music_string[i] == 32 )
    {
      if ( !strcmp(current, "o") )
      {
        if ( size == capacity )
        {
          if ( capacity <= 0 )
            v9 = 4;
          else
            v9 = 2 * capacity;
          capacity = v9;
          out = (int *)realloc(out, 4LL * v9);
        }
        v3 = size++;
        out[v3] = 4;
      }
      if ( !strcmp(current, "o|") )
      {
        if ( size == capacity )
        {
          if ( capacity <= 0 )
            v8 = 4;
          else
            v8 = 2 * capacity;
          capacity = v8;
          out = (int *)realloc(out, 4LL * v8);
        }
        v4 = size++;
        out[v4] = 2;
      }
      if ( !strcmp(current, ".|") )
      {
        if ( size == capacity )
        {
          if ( capacity <= 0 )
            v7 = 4;
          else
            v7 = 2 * capacity;
          capacity = v7;
          out = (int *)realloc(out, 4LL * v7);
        }
        v5 = size++;
        out[v5] = 1;
      }
      strcpy(current, "");
    }
    else
    {
      len = strlen(current);
      if ( len < 2 )
      {
        current[len] = temp_music_string[i];
        current[len + 1] = 0;
      }
    }
  }
  free(temp_music_string);
  *counta = size;
  return out;
}