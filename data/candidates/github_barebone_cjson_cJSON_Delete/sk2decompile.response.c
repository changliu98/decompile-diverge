void cJSON_Delete(cJSON *c) {
  cJSON *next;
  while (c) {
    next = c->next;
    if (!(c->type & 256) && c->child) {
      cJSON_Delete(c->child);
    }
    if (!(c->type & 256) && c->valuestring) {
      global_hooks.deallocate(c->valuestring);
      c->valuestring = 0;
    }
    if (!(c->type & 512) && c->string) {
      global_hooks.deallocate(c->string);
      c->string = 0;
    }
    global_hooks.deallocate(c);
    c = next;
  }
}