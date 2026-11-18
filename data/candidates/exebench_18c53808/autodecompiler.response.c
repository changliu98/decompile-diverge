void gui_combine_scissor( rectDef_t *r, clipHandle_t *handle ) {
 int i;
 vec4_t itemClip[4];
 vec4_t windowClip[4];

 if ( !handle ) {
  return;
 }

 windowClip[0] = r->x;
 windowClip[1] = r->y;
 windowClip[2] = r->x + r->w;
 windowClip[3] = r->y + r->h;

 itemClip[0] = handle->window.x;
 itemClip[1] = handle->window.y;
 itemClip[2] = handle->window.x + handle->window.w;
 itemClip[3] = handle->window.y + handle->window.h;


 for ( i = 0; i < 2; i++ )
 {
  if ( windowClip[i] > itemClip[i] ) {
   windowClip[i] = itemClip[i];
  }
 }


 for ( i = 2; i < 4; i++ )
 {
  if ( windowClip[i] < itemClip[i] ) {
   windowClip[i] = itemClip[i];
  }
 }

 r->x = windowClip[0];
 r->y = windowClip[1];
 r->w = windowClip[2] - windowClip[0];
 r->h = windowClip[3] - windowClip[1];
}