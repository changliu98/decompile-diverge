void string_rip( char *str, const char *ripper )
{
   char *t_ptr;
   const char *r_ptr;
   int do_rip;

   t_ptr = str;

   while ( *str )
   {
      do_rip = 0;

      for ( r_ptr = ripper; *r_ptr; r_ptr++ )
      {
         if ( *str == *r_ptr )
         {
            do_rip = 1;
            break;
         }
      }

      if ( !do_rip )
      {
         *t_ptr = *str;
         t_ptr++;
      }

      str++;
   }

   *t_ptr = '\0';
}