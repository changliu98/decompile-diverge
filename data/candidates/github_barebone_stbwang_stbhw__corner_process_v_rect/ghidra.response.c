void stbhw__corner_process_v_rect
               (stbhw__process *p,int xpos,int ypos,int a,int b,int c,int d,int e,int f)

{
  int len_00;
  int len;
  int c_local;
  int b_local;
  int a_local;
  int ypos_local;
  int xpos_local;
  stbhw__process *p_local;
  
  len_00 = p->c->short_side_len;
  stbhw__draw_hline(p->data,p->stride,xpos + 1,ypos,stbhw__corner_colors_to_edge_color[a][d],len_00,
                    0);
  stbhw__draw_vline(p->data,p->stride,xpos,ypos + 1,stbhw__corner_colors_to_edge_color[a][b],len_00,
                    5);
  stbhw__draw_vline(p->data,p->stride,xpos + len_00 + 1,ypos + 1,
                    stbhw__corner_colors_to_edge_color[d][e],len_00,1);
  stbhw__draw_vline(p->data,p->stride,xpos,ypos + len_00 + 1,
                    stbhw__corner_colors_to_edge_color[b][c],len_00,4);
  stbhw__draw_vline(p->data,p->stride,xpos + len_00 + 1,ypos + len_00 + 1,
                    stbhw__corner_colors_to_edge_color[e][f],len_00,5);
  stbhw__draw_hline(p->data,p->stride,xpos + 1,ypos + len_00 * 2 + 1,
                    stbhw__corner_colors_to_edge_color[c][f],len_00,3);
  if (p->c->corner_type_color_template[0][a] != 0) {
    stbhw__draw_clipped_corner(p->data,p->stride,xpos,ypos,len_00,len_00 << 1,1,1);
  }
  if (p->c->corner_type_color_template[3][b] != 0) {
    stbhw__draw_clipped_corner(p->data,p->stride,xpos,ypos,len_00,len_00 << 1,1,len_00 + 1);
  }
  if (p->c->corner_type_color_template[2][c] != 0) {
    stbhw__draw_clipped_corner(p->data,p->stride,xpos,ypos,len_00,len_00 << 1,1,len_00 * 2 + 1);
  }
  if (p->c->corner_type_color_template[1][d] != 0) {
    stbhw__draw_clipped_corner(p->data,p->stride,xpos,ypos,len_00,len_00 << 1,len_00 + 1,1);
  }
  if (p->c->corner_type_color_template[0][e] != 0) {
    stbhw__draw_clipped_corner(p->data,p->stride,xpos,ypos,len_00,len_00 << 1,len_00 + 1,len_00 + 1)
    ;
  }
  if (p->c->corner_type_color_template[3][f] != 0) {
    stbhw__draw_clipped_corner
              (p->data,p->stride,xpos,ypos,len_00,len_00 << 1,len_00 + 1,len_00 * 2 + 1);
  }
  stbhw__set_pixel(p->data,p->stride,xpos,ypos,stbhw__corner_colors[0][a]);
  stbhw__set_pixel(p->data,p->stride,xpos,ypos + len_00,stbhw__corner_colors[3][b]);
  stbhw__set_pixel(p->data,p->stride,xpos,ypos + len_00 * 2 + 1,stbhw__corner_colors[2][c]);
  stbhw__set_pixel(p->data,p->stride,xpos + len_00 + 1,ypos,stbhw__corner_colors[1][d]);
  stbhw__set_pixel(p->data,p->stride,xpos + len_00 + 1,ypos + len_00,stbhw__corner_colors[0][e]);
  stbhw__set_pixel(p->data,p->stride,xpos + len_00 + 1,ypos + len_00 * 2 + 1,
                   stbhw__corner_colors[3][f]);
  return;
}