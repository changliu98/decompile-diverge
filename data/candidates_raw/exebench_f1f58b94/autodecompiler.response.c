void sort_shorts(short *shorts)
{
 short tmp;
 {tmp = ((shorts[0]) < (shorts[1]) ? (shorts[0]) : (shorts[1])); ((shorts[0]) = (((shorts[0]) < (shorts[1]) ? (shorts[0]) : (shorts[1])))); ((shorts[1]) = (tmp));};
 {tmp = ((shorts[1]) < (shorts[2]) ? (shorts[1]) : (shorts[2])); ((shorts[1]) = (((shorts[1]) < (shorts[2]) ? (shorts[1]) : (shorts[2])))); ((shorts[2]) = (tmp));};
 {tmp = ((shorts[0]) < (shorts[1]) ? (shorts[0]) : (shorts[1])); ((shorts[0]) = (((shorts[0]) < (shorts[1]) ? (shorts[0]) : (shorts[1])))); ((shorts[1]) = (tmp));};
 {tmp = ((shorts[2]) < (shorts[3]) ? (shorts[2]) : (shorts[3])); ((shorts[2]) = (((shorts[2]) < (shorts[3]) ? (shorts[2]) : (shorts[3])))); ((shorts[3]) = (tmp));};
 {tmp = ((shorts[0]) < (shorts[2]) ? (shorts[0]) : (shorts[2])); ((shorts[0]) = (((shorts[0]) < (shorts[2]) ? (shorts[0]) : (shorts[2])))); ((shorts[2]) = (tmp));};
 {tmp = ((shorts[1]) < (shorts[3]) ? (shorts[1]) : (shorts[3])); ((shorts[1]) = (((shorts[1]) < (shorts[3]) ? (shorts[1]) : (shorts[3])))); ((shorts[3]) = (tmp));};
 {tmp = ((shorts[1]) < (shorts[2]) ? (shorts[1]) : (shorts[2])); ((shorts[1]) = (((shorts[1]) < (shorts[2]) ? (shorts[1]) : (shorts[2])))); ((shorts[2]) = (tmp));};
}