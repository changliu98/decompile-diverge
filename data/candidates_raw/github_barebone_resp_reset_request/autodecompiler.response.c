void
reset_request(struct http_request *req)
{
 if (req == NULL)
  return;

 struct http_request *r = req;
 r->method = 0;
 r->version_major = 0;
 r->version_minor = 0;
 if (r->url != NULL)
  free(r->url);
 r->url = NULL;
 r->content_type = NULL;
 r->content_length = 0;
 r->body = NULL;
}