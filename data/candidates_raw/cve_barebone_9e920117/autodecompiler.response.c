static long
file_open( struct forth_instance *fi,
           struct string *fname, struct file *f ) {
  long ret;
  size_t len;
  char path[4096];
  char *p;
  size_t trail = 0;

  len = f->name.size;

  if ( fname ) {
    len = fname->len;
    if ( !len ) { ret = -3; goto exit; }
    trail = ( fname->data[fname->len-1] != '/' ) ? 1 : 0;
    if ( trail ) len++;
  }

  if ( len > sizeof(path) ) { ret = -1; goto exit; }

  p = path;

  if ( fname ) {
    memcpy( p, fname->data, fname->len );
    p += fname->len;
    if ( trail ) *p++ = '/';
  } else {
    memcpy( p, f->name.data, f->name.size );
    p += f->name.size;
    *p = '\0';
    p = realpath( path, f );
    if ( !p ) { ret = -3; goto exit; }
    f->fd = open( p, 0 );
    if ( f->fd < 0 ) { ret = -3; goto exit; }
    f->path = &f->name;
    f->pathlen = strlen( f->path );
  }

  ret = 0;

exit:
  return ret;
}