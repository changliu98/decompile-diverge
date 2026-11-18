static u32 GetHintFormat( qt_atom *track )
{
 u32 duration;
 qt_atom *tkhd, *mdhd, *hdlr;
 qt_atom *stts;

 tkhd = track->list->list[5];
 if ( tkhd->id != ((('t')<<24)|(('k')<<16)|(('h')<<8)|('d')) ) {
  duration = 0;
 } else if ( !tkhd || !tkhd->list ) {

  mdhd = track->list->list[5]->list[5];
  if ( !tkhd ) {
   if ( mdhd ) {
    duration = mdhd->duration;
   } else {
    stts = gf_list_get(track->list->list[5]->list[5]->list, 0);
    if ( stts ) {
     duration = stts->duration;
    } else {
     duration = 0;
    }
   }
  } else {
   if ( stts ) tkhd->duration = stts->duration;
   duration = tkhd->duration;
  }
 } else {
  duration = tkhd->duration;
 }

 return duration;
}