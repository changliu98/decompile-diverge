const char *xf_Pointer_get_window(XMLRPC_VALUE value) {
   const char *ret;

   if(!value) {
      ret = NULL;
   }
   else if(!value->id.len) {
      ret = NULL;
   }
   else if(!value->i) {
      ret = NULL;
   }
   else {
      ret = value->i->id.str;
   }
   return ret;
}