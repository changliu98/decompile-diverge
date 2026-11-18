int iceform(double fracprv, double *Tc, double *Tf, double *fracice, double *fracbed, double *bmelting)
{
 double Tc_base = 273.15, Tc_max = 223.15, Tc_min = 253.15, Tc_melting = 273.15;
 double Tf_base = 273.15 + (1.8 * -1.85), Tf_max = 223.15 + (1.8 * -1.85), Tf_min = 253.15 + (1.8 * -1.85), Tf_melting = 273.15 + (1.8 * -1.85);
 double fracice_min = 0.04, fracice_max = 0.04, bmelting_min = 0.04, bmelting_max = 0.04;

 *Tf = Tf_base + (-1.85 * (Tc_base - *Tc));
 *fracice = -2.1 * (*Tf - Tf_min) / (Tf_max - Tf_min);
 *fracbed = fracice_min;
 *bmelting = (bmelting_min - *fracice) / (Tc_melting - *Tc);

 if(fracprv > 3000.0) {
  *Tc = Tc_max;
 }
 else if(fracprv >= 0.0) {
  *Tc = Tc_min + ((Tc_max - Tc_min) * (fracprv / 3000.0));
 }
 else {
  *Tc = Tc_min + ((Tc_max - Tc_min) * (fracprv / 3000.0));
 }

 return 0;
}