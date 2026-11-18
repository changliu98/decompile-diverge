CURLcode __cdecl Curl_smtp_escape_eob(connectdata *conn, const ssize_t nread)
{
  ssize_t v2; // rcx
  size_t eob_sent; // [rsp+8h] [rbp-58h]
  char *oldscratch; // [rsp+10h] [rbp-50h]
  char *newscratch; // [rsp+18h] [rbp-48h]
  char *scratch; // [rsp+20h] [rbp-40h]
  SMTP *smtp; // [rsp+28h] [rbp-38h]
  Curl_easy *data; // [rsp+30h] [rbp-30h]
  ssize_t si_0; // [rsp+38h] [rbp-28h]
  ssize_t i; // [rsp+40h] [rbp-20h]

  data = conn->data;
  smtp = (SMTP *)conn->data->req.protop;
  scratch = conn->data->state.scratch;
  newscratch = 0LL;
  oldscratch = 0LL;
  if ( scratch && !data->set.crlf
    || (oldscratch = conn->data->state.scratch,
        newscratch = (char *)malloc(2 * data->set.buffer_size),
        (scratch = newscratch) != 0LL) )
  {
    eob_sent = smtp->eob;
    i = 0LL;
    si_0 = 0LL;
    while ( i < nread )
    {
      if ( asc_2024[smtp->eob] == data->req.upload_fromhere[i] )
      {
        smtp->trailing_crlf = ++smtp->eob == 2 || smtp->eob == 5;
      }
      else if ( smtp->eob )
      {
        memcpy(&scratch[si_0], &asc_2024[eob_sent], smtp->eob - eob_sent);
        si_0 += smtp->eob - eob_sent;
        smtp->eob = asc_2024[0] == data->req.upload_fromhere[i];
        eob_sent = 0LL;
        smtp->trailing_crlf = 0;
      }
      if ( smtp->eob == 3 )
      {
        memcpy(&scratch[si_0], &asc_202A[eob_sent], 4 - eob_sent);
        si_0 += 4 - eob_sent;
        smtp->eob = 0LL;
        eob_sent = 0LL;
      }
      else if ( !smtp->eob )
      {
        v2 = si_0++;
        scratch[v2] = data->req.upload_fromhere[i];
      }
      ++i;
    }
    if ( smtp->eob != eob_sent )
    {
      memcpy(&scratch[si_0], &asc_2024[eob_sent], smtp->eob - eob_sent);
      si_0 += smtp->eob - eob_sent;
    }
    if ( si_0 == nread )
    {
      free(newscratch);
    }
    else
    {
      data->req.upload_fromhere = scratch;
      data->state.scratch = scratch;
      free(oldscratch);
      data->req.upload_present = si_0;
    }
    return 0;
  }
  else
  {
    Curl_failf(data, "Failed to alloc scratch buffer!");
    return 27;
  }
}