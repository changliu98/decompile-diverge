void stb_linear_controller(float *curpos,float target_pos,float acc,float deacc,float dt)

{
  float cp;
  float p;
  float sign;
  float dt_local;
  float deacc_local;
  float acc_local;
  float target_pos_local;
  float *curpos_local;
  
  sign = DAT_00102004;
  cp = *curpos;
  if ((cp != target_pos) || (NAN(cp) || NAN(target_pos))) {
    target_pos_local = target_pos;
    if (target_pos < cp) {
      target_pos_local = -target_pos;
      cp = -cp;
      sign = DAT_00102008;
    }
    dt_local = dt;
    if (cp < 0.0) {
      p = deacc * dt + cp;
      if (p <= 0.0) {
        dt_local = 0.0;
      }
      else {
        p = 0.0;
        dt_local = dt - cp / deacc;
        if (dt_local < 0.0) {
          dt_local = 0.0;
        }
      }
      cp = p;
    }
    p = acc * dt_local + cp;
    if (target_pos_local < p) {
      p = target_pos_local;
    }
    *curpos = p * sign;
  }
  return;
}