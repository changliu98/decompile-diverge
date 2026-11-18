void pid_move(float *curpos, float target_pos, float acc, float deacc, float dt)
{
  float target_pos_ = target_pos;
  float dt_ = dt;
  float sign = 1.0;
  float curpos_ = *curpos;
  if (curpos_ != target_pos)
  {
    if (curpos_ > target_pos)
    {
      target_pos_ = -target_pos_;
      curpos_ = -curpos_;
      sign = -1.0;
    }
    if (curpos_ < 0.0f)
    {
      curpos_ = curpos_ + deacc * dt_;
      if (curpos_ > 0.0f)
      {
        curpos_ = 0.0f;
        dt_ = dt_ - curpos_ / deacc;
        if (dt_ < 0.0f)
        {
          dt_ = 0.0f;
        }
      }
      else
      {
        dt_ = 0.0f;
      }
    }
    curpos_ = curpos_ + acc * dt_;
    if (curpos_ > target_pos_)
    {
      curpos_ = target_pos_;
    }
    *curpos = curpos_ * sign;
  }
}