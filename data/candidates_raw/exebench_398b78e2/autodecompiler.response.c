float LowPassFilter2p_apply(float sample, struct LowPassFilter2p *filter)
{
 float delay_element_0;
 float output;

 delay_element_0 = sample * filter->c0 + filter->delay_element_1 * filter->c1 + filter->delay_element_2 * filter->c2;
 filter->delay_element_2 = filter->delay_element_1;
 filter->delay_element_1 = delay_element_0;


 output = delay_element_0 * filter->c3 + filter->delay_element_1 * filter->c4 + filter->delay_element_2 * filter->c5;

 return output;
}