









void
calculate_proportions( int src_w, int src_h, int *pdst_w, int *pdst_h )
{
 int dst_w = pdst_w?*pdst_w:0 ;
 int dst_h = pdst_h?*pdst_h:0 ;

 if( src_w > 0 && src_w >= src_h && (dst_w > 0 || dst_h <= 0))
  dst_h = (src_h*dst_w)/src_w ;
 else if( src_h > 0 )
  dst_w = (src_w*dst_h)/src_h ;

 if( pdst_w ) *pdst_w = dst_w ;
 if( pdst_h ) *pdst_h = dst_h ;
}
