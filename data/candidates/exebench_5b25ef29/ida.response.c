void __cdecl find_next_cell(int *ijkn, int *current_ijk, int *face_sect, double *vv, int *next_ijk)
{
  int face1_sect[3]; // [rsp+0h] [rbp-40h]
  int flag; // [rsp+Ch] [rbp-34h]
  int m; // [rsp+10h] [rbp-30h]
  int j; // [rsp+14h] [rbp-2Ch]
  int *next_ijka; // [rsp+18h] [rbp-28h]
  double *vva; // [rsp+20h] [rbp-20h]
  int *face_secta; // [rsp+28h] [rbp-18h]
  int *current_ijka; // [rsp+30h] [rbp-10h]
  int *ijkna; // [rsp+38h] [rbp-8h]

  ijkna = ijkn;
  current_ijka = current_ijk;
  face_secta = face_sect;
  vva = vv;
  next_ijka = next_ijk;
  flag = 1;
  for ( j = 0; j < 3; ++j )
    face1_sect[j] = face_secta[j];
  for ( j = 0; j < 3; ++j )
    next_ijka[j] = current_ijka[j];
  for ( m = 0; m < 3; ++m )
  {
    if ( face_secta[m] != -1 )
    {
      if ( face_secta[m] )
      {
        switch ( face_secta[m] )
        {
          case 1:
            if ( *vva > 0.0 )
            {
              *next_ijka = *current_ijka + 1;
              face1_sect[m] = 0;
              if ( *next_ijka > *ijkna - 1 )
                goto LABEL_34;
            }
            break;
          case 2:
            if ( vva[1] < 0.0 )
            {
              next_ijka[1] = current_ijka[1] - 1;
              face1_sect[m] = 3;
              if ( next_ijka[1] < 0 )
                goto LABEL_34;
            }
            break;
          case 3:
            if ( vva[1] > 0.0 )
            {
              next_ijka[1] = current_ijka[1] + 1;
              face1_sect[m] = 2;
              if ( next_ijka[1] > ijkna[1] - 1 )
                goto LABEL_34;
            }
            break;
          case 4:
            if ( vva[2] < 0.0 )
            {
              next_ijka[2] = current_ijka[2] - 1;
              face1_sect[m] = 5;
              if ( next_ijka[2] < 0 )
                goto LABEL_34;
            }
            break;
          default:
            if ( face_secta[m] == 5 && vva[2] > 0.0 )
            {
              next_ijka[2] = current_ijka[2] + 1;
              face1_sect[m] = 4;
              if ( next_ijka[2] > ijkna[2] - 1 )
                goto LABEL_34;
            }
            break;
        }
      }
      else if ( *vva < 0.0 )
      {
        *next_ijka = *current_ijka - 1;
        face1_sect[m] = 1;
        if ( *next_ijka < 0 )
          break;
      }
    }
  }
LABEL_34:
  for ( m = 0; m < 3; ++m )
    face_secta[m] = face1_sect[m];
}