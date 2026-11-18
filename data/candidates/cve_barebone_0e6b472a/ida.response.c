int __cdecl AVI_read_audio(avi_t *AVI, u8 *audbuf, int bytes, int *continuous)
{
  track_t *v4; // rax
  track_t *v5; // rax
  track_t *v6; // rax
  int left; // [rsp+Ch] [rbp-44h]
  int todo; // [rsp+20h] [rbp-30h]
  int nr; // [rsp+24h] [rbp-2Ch]
  int bytesa; // [rsp+34h] [rbp-1Ch]

  bytesa = bytes;
  if ( AVI->mode )
  {
    if ( AVI->track[AVI->aptr].audio_index )
    {
      nr = 0;
      if ( !bytes )
      {
        v4 = &AVI->track[AVI->aptr];
        ++v4->audio_posc;
        AVI->track[AVI->aptr].audio_posb = 0;
      }
      *continuous = 1;
      while ( bytesa > 0 )
      {
        left = LODWORD(AVI->track[AVI->aptr].audio_index[AVI->track[AVI->aptr].audio_posc].len)
             - AVI->track[AVI->aptr].audio_posb;
        if ( left )
        {
          if ( bytesa >= left )
            todo = LODWORD(AVI->track[AVI->aptr].audio_index[AVI->track[AVI->aptr].audio_posc].len)
                 - AVI->track[AVI->aptr].audio_posb;
          else
            todo = bytesa;
          gf_fseek(
            AVI->fdes,
            AVI->track[AVI->aptr].audio_posb + AVI->track[AVI->aptr].audio_index[AVI->track[AVI->aptr].audio_posc].pos,
            0);
          if ( avi_read(AVI->fdes, (char *)&audbuf[nr], todo) != (__int64)todo )
          {
            AVI_errno = 3;
            return -1;
          }
          bytesa -= todo;
          nr += todo;
          v6 = &AVI->track[AVI->aptr];
          v6->audio_posb += todo;
        }
        else
        {
          if ( AVI->track[AVI->aptr].audio_posc >= AVI->track[AVI->aptr].audio_chunks - 1 )
            return nr;
          v5 = &AVI->track[AVI->aptr];
          ++v5->audio_posc;
          AVI->track[AVI->aptr].audio_posb = 0;
          *continuous = 0;
        }
      }
      return nr;
    }
    else
    {
      AVI_errno = 13;
      return -1;
    }
  }
  else
  {
    AVI_errno = 7;
    return -1;
  }
}