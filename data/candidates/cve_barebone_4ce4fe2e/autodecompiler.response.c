static void gf_av1_reset_state(GF_MemoryStream *ms, int destroy)
{
 if (ms->tracks) {
  while (gf_list_count(ms->tracks)) {
   GF_MemoryStreamTrack *tr = gf_list_pop_back(ms->tracks);
   if (tr->data) gf_free(tr->data);
   gf_free(tr);
  }
 } else if (ms->tracks_to_delete) {
  while (gf_list_count(ms->tracks_to_delete)) {
   GF_MemoryStreamTrack *tr = gf_list_pop_back(ms->tracks_to_delete);
   if (tr->data) gf_free(tr->data);
   gf_free(tr);
  }
 }

 GF_List *to_delete = ms->tracks_to_delete;
 GF_List *to_add = ms->tracks;

 memset(&ms->track_info, 0, sizeof(GF_MemoryStreamTrackInfo));
 ms->track_info.track_id = 1;

 if (destroy) {
  gf_list_del(to_delete);
  gf_list_del(to_add);

  if (ms->bs) {
   if (gf_bs_get_position(ms->bs)) {
    u32 size;
    gf_bs_get_content_no_truncate(ms->bs, &ms->data, &size, &ms->data_size);
   }
   gf_bs_del(ms->bs);
  }
  ms->bs = NULL;
 } else {
  ms->tracks_to_delete = to_delete;
  ms->tracks = to_add;
  if (ms->bs) gf_bs_seek(ms->bs, 0);
 }
}