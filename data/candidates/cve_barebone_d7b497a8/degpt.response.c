CURLcode Curl_smtp_escape_eob(connectdata *conn,ssize_t nread)

{
  Curl_easy *data_00;
  size_t *psVar1;
  long lVar2;
  size_t eob_sent;
  char *oldscratch;
  char *newscratch;
  char *scratch;
  SMTP *smtp;
  Curl_easy *data;
  ssize_t si;
  ssize_t i;
  ssize_t nread_local;
  connectdata *conn_local;
  CURLcode local_c;
  
  data_00 = conn->data;
  psVar1 = (data_00->req).protop;
  scratch = (data_00->state).scratch;
  newscratch = (char *)0x0;
  oldscratch = (char *)0x0;
  if (((scratch == (char *)0x0) || (((data_00->set).crlf & 1U) != 0)) &&
     (newscratch = malloc((data_00->set).buffer_size << 1), oldscratch = scratch,
     scratch = newscratch, newscratch == (char *)0x0)) {
    Curl_failf(data_00,"Failed to alloc scratch buffer!");
    local_c = CURLE_OUT_OF_MEMORY;
  }
  else {
    eob_sent = *psVar1;
    si = 0;
    for (i = 0; i < nread; i = i + 1) {
      if ("\r\n.\r\n"[*psVar1] == (data_00->req).upload_fromhere[i]) {
        *psVar1 = *psVar1 + 1;
        if ((*psVar1 == 2) || (*psVar1 == 5)) {
          *(undefined1 *)(psVar1 + 1) = 1;
        }
        else {
          *(undefined1 *)(psVar1 + 1) = 0;
        }
      }
      else if (*psVar1 != 0) {
        memcpy(scratch + si,"\r\n.\r\n" + eob_sent,*psVar1 - eob_sent);
        si = (*psVar1 - eob_sent) + si;
        if (s___00102024[0] == (data_00->req).upload_fromhere[i]) {
          *psVar1 = 1;
        }
        else {
          *psVar1 = 0;
        }
        eob_sent = 0;
        *(undefined1 *)(psVar1 + 1) = 0;
      }
      if (*psVar1 == 3) {
        memcpy(scratch + si,&DAT_0010202a + eob_sent,4 - eob_sent);
        lVar2 = 4 - eob_sent;
        *psVar1 = 0;
        eob_sent = 0;
        si = lVar2 + si;
      }
      else if (*psVar1 == 0) {
        scratch[si] = (data_00->req).upload_fromhere[i];
        si = si + 1;
      }
    }
    if (*psVar1 != eob_sent) {
      memcpy(scratch + si,"\r\n.\r\n" + eob_sent,*psVar1 - eob_sent);
      si = (*psVar1 - eob_sent) + si;
    }
    if (si == nread) {
      free(newscratch);
    }
    else {
      (data_00->req).upload_fromhere = scratch;
      (data_00->state).scratch = scratch;
      free(oldscratch);
      (data_00->req).upload_present = si;
    }
    local_c = CURLE_OK;
  }
  return local_c;
}