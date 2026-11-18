void reset_request(request *req) {
  if (req == NULL) return;
  req->method = 0;
  req->uri = 0;
  req->version = 0;
  if (req->headers != NULL) free(req->headers);
  req->headers = NULL;
  req->header_count = 0;
  req->header_size = 0;
  req->header_max = 0;
}