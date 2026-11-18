static int archive_string_append_from_wcs(struct mg_connection *nc, const struct http_message *hm,
                    size_t chunk_len) {
  char buf[16];
  size_t len;
  int n;
  int r = 0;

  do {
    memset(buf, 0, sizeof(buf));
    len = nc->recv_mbuf.len + chunk_len + 1;
    while (mg_recv(nc, buf, sizeof(buf)) > 0) {
      len = nc->recv_mbuf.len;
      if (hm->chunked) {
        if (chunk_len > 0) {
          n = mg_vcpy(buf + nc->recv_mbuf.len, hm->body.p, chunk_len);
          if (n == -1) {
            if (mg_connection_get_if(nc)->proto == MG_PROTO_HTTP) {
              buf[nc->recv_mbuf.len++] = '?';
              r = -1;
            }
          } else {
            nc->recv_mbuf.len += n;
            chunk_len -= n;
          }
        } else {
          r = -1;
        }
      } else {
        r = -1;
      }
    }
    nc->recv_mbuf.len = len;
    buf[nc->recv_mbuf.len] = '\0';
  } while (r == -1);

  return r;
}