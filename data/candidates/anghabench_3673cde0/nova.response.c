float modff(float x, float *iptr)
{
	float_t y;
	uint32_t ix,lx;

	EXTRACT_WORDS(lx,x);
	ix = lx&0x7fffffff;
    
	if (ix<0x3f800000+(1<<23)) {
	    *iptr = x;
	    if (ix<0x3f800000-((1<<23)+1)) {
		if (huge+x>0.0)			
			return x;
	    }
	    return tiny*2;
	}
    
	y = x*x;
    
	if (ix<0x3f800000+(1<<23)+1) {
	    *iptr = x;
	    return y;
	}
    
	if (ix<=0x3f800000+((1<<24)-1)) {
	    RETURN_WORDS(lx,y);
	    *iptr = (float) (((int) (lx>>32))<<32);
	    return y;
	}
    
	if (y==0)
	    return x;
	*iptr = x;
	return y;
}