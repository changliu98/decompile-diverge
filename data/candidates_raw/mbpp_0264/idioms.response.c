static double h_age_to_size(int h_age)
{
  if ( h_age < 0 )
    exit(1);
  if ( h_age <= 2 )
    return h_age * 10.5;
  else
    return ( ( h_age - 2 ) * 4 + 21 );
}