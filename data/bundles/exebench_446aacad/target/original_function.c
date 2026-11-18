int cond_read_lock( int *lk )
{
   int result;
   ;;
   if (*lk>=0) {
      *lk = *lk + 1;
      result = 1;
   }
   else {
      result = 0;
   }
   ;;
   return result;
}