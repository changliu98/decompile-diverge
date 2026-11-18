CURLcode Curl_smtp_escape_eob(struct connectdata *conn,
                                     ssize_t nread)
{
  Curl_easy *data = conn->data;
  struct Curl_easy_dups *d = &data->easy_dups;
  struct smtp_conn *smtpc = &d->proto.smtpc;
  struct SessionHandle *data_s = data->req.protop;
  char *scratch = data->state.scratch;
  char *newscratch = NULL;
  char *oldscratch = NULL;
  const char *eob = "\r\n.\r\n";
  ssize_t i, si;
  size_t eob_sent;

  if(!scratch || (data->set.crlf & 1)) {
    /* We need a scratch area to work in */
    newscratch = malloc(data->set.buffer_size * 2);
    if(!newscratch) {
      Curl_failf(data, "Failed to alloc scratch buffer!");
      return CURLE_OUT_OF_MEMORY;
    }
    oldscratch = scratch;
    scratch = newscratch;
  }

  eob_sent = data_s->eob_sent;
  si = 0;
  for(i = 0; i < nread; i++) {
    if(data->req.upload_fromhere[i] == eob[data_s->eob_sent]) {
      /* The current letter matched the EOB sequence! */
      data_s->eob_sent++;
      if(data_s->eob_sent == 2 || data_s->eob_sent == 5)
        data_s->eob_quoted = 1;
      else
        data_s->eob_quoted = 0;
    }
    else if(data_s->eob_sent) {
      /* The current letter didn't match the EOB sequence, but the previous
         letter did! */
      memcpy(&scratch[si], &eob[eob_sent], data_s->eob_sent - eob_sent);
      si += data_s->eob_sent - eob_sent;
      if(data->req.upload_fromhere[i] == eob[0])
        /* The current letter is the first letter of the EOB sequence! */
        data_s->eob_sent = 1;
      else
        /* The current letter is not the first letter of the EOB sequence! */
        data_s->eob_sent = 0;
      eob_sent = 0;
      data_s->eob_quoted = 0;
    }
    if(data_s->eob_sent == 3) {
      /* The previous letter matched the EOB sequence and the current letter
         is the third letter of the EOB sequence! */
      memcpy(&scratch[si], &eob[eob_sent], 4 - eob_sent);
      si += 4 - eob_sent;
      data_s->eob_sent = 0;
      eob_sent = 0;
    }
    else if(!data_s->eob_sent) {
      /* The current letter is not the first letter of the EOB sequence! */
      scratch[si] = data->req.upload_fromhere[i];
      si++;
    }
  }
  if(data_s->eob_sent != eob_sent) {
    /* The last letter didn't match the EOB sequence, but the previous letter
       did! */
    memcpy(&scratch[si], &eob[eob_sent], data_s->eob_sent - eob_sent);
    si += data_s->eob_sent - eob_sent;
  }

  if(si == nread) {
    /* We didn't change anything! */
    free(newscratch);
  }
  else {
    /* We changed the buffer! */
    data->req.upload_fromhere = (unsigned char *) scratch;
    data->state.scratch = scratch;
    free(oldscratch);
    data->req.upload_present = si;
  }

  return CURLE_OK;
}