static CURLcode Curl_smtp_escape_eob(struct connectdata *conn, curl_off_t size)
{
  struct smtp_conn *smtpc = conn->data->req.protoptr;
  char *buf = conn->data->state.buffer;
  char *scratch = NULL;
  char *old_scratch = NULL;
  int eob_sent;
  size_t i, si;
  CURLcode result;

  if(!buf || (conn->data->set.opt_no_body & 1)) {
    old_scratch = buf;
    buf = scratch = (char *) malloc(conn->data->set.upload_buffer_size * 2);
    if(!scratch) {
      Curl_failf(conn->data, "Failed to alloc scratch buffer!");
      result = 27;
      goto out;
    }
  }
  else {
    eob_sent = smtpc->eob;
    for(i = 0, si = 0; i < size;) {
      if(buf[i] == "\r\n.\r\n"[smtpc->eob]) {
        smtpc->eob++;
        if(smtpc->eob == 2 || smtpc->eob == 5)
          smtpc->eob_dot = 1;
        else
          smtpc->eob_dot = 0;
      }
      else {
        if(smtpc->eob) {
          memcpy(&buf[si], &"\r\n.\r\n"[eob_sent], smtpc->eob - eob_sent);
          si += smtpc->eob - eob_sent;
          if(buf[i] == "\r\n.\r\n"[0])
            smtpc->eob = 1;
          else
            smtpc->eob = 0;
          eob_sent = 0;
          smtpc->eob_dot = 0;
        }
      }

      if(smtpc->eob == 3) {
        memcpy(&buf[si], &"\r\n..\0", 4 - eob_sent);
        si += 4 - eob_sent;
        smtpc->eob = 0;
        eob_sent = 0;
      }
      else if(!smtpc->eob)
        buf[si++] = buf[i];

      i++;
    }

    if(smtpc->eob - eob_sent)
      memcpy(&buf[si], &"\r\n.\r\n"[eob_sent], smtpc->eob - eob_sent);

    if(si != size) {
      conn->data->state.buffer = buf;
      conn->data->state.scratch = buf;
      free(old_scratch);
      conn->data->state.buffer_size = si;
    }
    else
      free(scratch);
  }

  result = 0;

out:
  return result;
}