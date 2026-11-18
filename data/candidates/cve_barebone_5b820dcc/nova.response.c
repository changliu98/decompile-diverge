static int libusb_udev_select_interface(struct SN_env * z, unsigned char r, unsigned char s) { 
    {   int c1 = z->I[1]; 
        {   int c2 = z->I[0]; 
            {   int mlimit1; 
                if (c2 == 0) goto lab0;
                mlimit1 = c2;
                {   int c3 = z->I[2]; 
                    if (c3 == 0) goto lab0;
                    mlimit1 = c3;
                }
            }
            {   int c2 = z->I[3]; 
                if (c2 == 0) goto lab0;
                mlimit1 = c2;
            }
        lab0:
            z->bra = z->c - mlimit1;
        }
        {   int m2 = z->l - z->c; (void)m2; 
            z->ket = z->c; 
            if (z->c <= z->lb || z->p[z->c - 1]!= r) { goto lab2; } 
            z->c++;
            {   int m3 = z->l - z->c; (void)m3; 
                z->ket = z->c; 
                if (z->c <= z->lb || z->p[z->c - 1]!= s) { goto lab3; } 
                z->c++;
                return 1;
            lab3:
                z->c = z->ket;
            }
        lab2:
            z->c = z->bra;
        }
        return -1;
    }
}