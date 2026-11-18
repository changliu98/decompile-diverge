void julian_to_date(long julian, long *mm, long *id, long *iyyy)
{
 long ja,jalpha,jb,jc,jd,je;

 ja=julian+68569;
 jalpha=(4*ja)/146097;
 jb=ja-(146097*jalpha+3)/4;
 jc=(4000*(jb+1))/1461001;
 jd=jb-((1461*jc)/4)+31;
 je=(80*jd)/2447;
 *id=jd-((2447*je)/80);
 *mm=je/11;
 *iyyy=100*(jalpha-49)+jc+je;
}