int
sock_initaddress(char *host, char *port, struct addrinfo *hints,
                 struct addrinfo **addrinfo, char *errbuf, int errbuflen)
{
    char *portstr;
    int retval, ret;
    char *func = "sock_initaddress";
# 103 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/SageAxcess/pcap-ndis6/refs/heads/dev-open/src/libpcap/sockutils.c"
    char *host_name = host;






    if (port == NULL)
    {
        portstr = "0";
    }
    else
    {
        portstr = port;
    }

    retval = getaddrinfo(host_name, portstr, hints, addrinfo);

    if (retval != 0)
    {
        if (errbuf != NULL)
        {





            if ((host != NULL) && (port != NULL))
            {



                ret = getaddrinfo(host, NULL, hints, addrinfo);

                if (ret == 0)
                {
                    freeaddrinfo(*addrinfo);
                    get_gai_errstring(errbuf, errbuflen, "getaddrinfo(): invalid port", retval, NULL, port);
                }
                else
                {
                    get_gai_errstring(errbuf, errbuflen, "getaddrinfo(): invalid port", retval, host, NULL);
                }
            }
            else
            {
                get_gai_errstring(errbuf, errbuflen, "getaddrinfo(): invalid port", retval, host, port);
            }
        }
        else
        {
            retval = -1;
        }
    }
    else
    {






        if (((*addrinfo)->ai_socktype != 2) &&
            ((*addrinfo)->ai_socktype != 10))
        {
            if (errbuf != NULL)
            {
                snprintf(errbuf, errbuflen,
                         "getaddrinfo(): socket type not supported");
            }
            freeaddrinfo(*addrinfo);
            (*addrinfo) = NULL;
            retval = -1;
        }
        else if (((*addrinfo)->ai_protocol == 1) &&
                 (sock_ismcastaddr((struct sockaddr *)((*addrinfo)->ai_addr)) == 0))
        {
            if (errbuf != NULL)
            {
                snprintf(errbuf, errbuflen,
                         "getaddrinfo(): multicast addresses are not valid when using TCP socket type");
            }
            freeaddrinfo(*addrinfo);
            (*addrinfo) = NULL;
            retval = -1;
        }
        else
        {
            retval = 0;
        }
    }





    return retval;
}