static CURLcode Curl_smtp_escape_eob(struct connectdata *conn,
                                     ssize_t datasize) {
  struct Curl_easy *data = conn->data;
  struct SMTP *smtp = data->req.protop;
  char *scratch = data->state.scratchbuffer;
  char *newscratch = NULL;
  char *oldscratch = NULL;
  ssize_t start;
  ssize_t len;
  ssize_t i;
  ssize_t j;
  static const char eob[] = {0x0d, 0x0a, 0x0d, 0x0a, 0x00};
  static const char eob2[] = {0x0d, 0x0a, 0x00};
  if ((scratch != NULL) && !data->set.dohostname) {
    oldscratch = scratch;
    newscratch = malloc(2 * data->set.max_send_size);
    scratch = newscratch;
  } else {
    oldscratch = scratch;
    newscratch = malloc(2 * data->set.max_send_size);
    scratch = newscratch;
    if (!scratch) {
      Curl_failf(data, "Failed to alloc scratch buffer!");
      return 27;
    }
  }
  start = smtp->eob_state;
  i = 0;
  j = 0;
  while (i < datasize) {
    if (eob[smtp->eob_state] == data->state.buffer[i]) {
      smtp->eob_state++;
      if ((smtp->eob_state == 2) || (smtp->eob_state == 5))
        smtp->eob_crlf = 1;
      else
        smtp->eob_crlf = 0;
    } else if (smtp->eob_state) {
      memcpy(scratch + j, eob + start, smtp->eob_state - start);
      j += smtp->eob_state - start;
      smtp->eob_state = (eob[0] == data->state.buffer[i]);
      start = 0;
      smtp->eob_crlf = 0;
    }
    if (smtp->eob_state == 3) {
      len = 4 - start;
      memcpy(scratch + j, eob2 + start, len);
      j += len;
      smtp->eob_state = 0;
      start = 0;
    } else if (smtp->eob_state == 0) {
      scratch[j++] = data->state.buffer[i];
    }
    i++;
  }
  if (smtp->eob_state != start) {
    len = smtp->eob_state - start;
    memcpy(scratch + j, eob + start, len);
    j += len;
  }
  if (j != datasize) {
    data->state.buffer = scratch;
    data->set.scratchbuffer = scratch;
    free(oldscratch);
    data->state.infilesize = j;
  } else
    free(newscratch);
  return 0;
}