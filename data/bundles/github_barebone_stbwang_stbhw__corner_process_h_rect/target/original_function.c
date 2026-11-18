static void stbhw__corner_process_h_rect(stbhw__process *p, int xpos, int ypos,
                            int a, int b, int c, int d, int e, int f)
{
   int len = p->c->short_side_len;

   stbhw__draw_hline(p->data, p->stride, xpos+1        , ypos        , stbhw__c2e[a][b], len, 2);
   stbhw__draw_hline(p->data, p->stride, xpos+  len+1  , ypos        , stbhw__c2e[b][c], len, 3);
   stbhw__draw_vline(p->data, p->stride, xpos          , ypos+1      , stbhw__c2e[a][d], len, 1);
   stbhw__draw_vline(p->data, p->stride, xpos+2*len+1  , ypos+1      , stbhw__c2e[c][f], len, 4);
   stbhw__draw_hline(p->data, p->stride, xpos+1        , ypos + len+1, stbhw__c2e[d][e], len, 0);
   stbhw__draw_hline(p->data, p->stride, xpos + len+1  , ypos + len+1, stbhw__c2e[e][f], len, 2);

   if (p->c->corner_type_color_template[1][a]) stbhw__draw_clipped_corner(p->data,p->stride, xpos,ypos, len*2,len, 1,1);
   if (p->c->corner_type_color_template[2][b]) stbhw__draw_clipped_corner(p->data,p->stride, xpos,ypos, len*2,len, len+1,1);
   if (p->c->corner_type_color_template[3][c]) stbhw__draw_clipped_corner(p->data,p->stride, xpos,ypos, len*2,len, len*2+1,1);

   if (p->c->corner_type_color_template[0][d]) stbhw__draw_clipped_corner(p->data,p->stride, xpos,ypos, len*2,len, 1,len+1);
   if (p->c->corner_type_color_template[1][e]) stbhw__draw_clipped_corner(p->data,p->stride, xpos,ypos, len*2,len, len+1,len+1);
   if (p->c->corner_type_color_template[2][f]) stbhw__draw_clipped_corner(p->data,p->stride, xpos,ypos, len*2,len, len*2+1,len+1);

   stbhw__set_pixel(p->data, p->stride, xpos        , ypos, stbhw__corner_colors[1][a]);
   stbhw__set_pixel(p->data, p->stride, xpos+len    , ypos, stbhw__corner_colors[2][b]);
   stbhw__set_pixel(p->data, p->stride, xpos+2*len+1, ypos, stbhw__corner_colors[3][c]);
   stbhw__set_pixel(p->data, p->stride, xpos        , ypos+len+1, stbhw__corner_colors[0][d]);
   stbhw__set_pixel(p->data, p->stride, xpos+len    , ypos+len+1, stbhw__corner_colors[1][e]);
   stbhw__set_pixel(p->data, p->stride, xpos+2*len+1, ypos+len+1, stbhw__corner_colors[2][f]);
}