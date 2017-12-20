# ft_nmap

42 school project

## Usage

```
./ft_nmap [options] ip
    --help
    --ip        [ip]
    -f/--file   [file] list of IP
    -p/--ports  [port number / port range] : default 1-1024
    -t/--thread [nb of thread] : default 0 - max 250
    --scan      [type] (SYN, NULL, ACK, FIN, XMAS, UDP) : default all
                ex: --scan SYN or --scan ACK-NULL-XMAS for multiple
                OPEN   CLOSE   FILTERED  UNFILTRED
```

## Todo

Scan to do:
- [x] SYN
- [x] NULL
- [x] ACK
- [x] FIN
- [x] XMAS
- [ ] UDP

- [ ] Choose the number of threads

- [ ] Parser -i (interface) eth0
- [ ] Parser print only open

- [ ] rDNS
- [X] find service
- [ ] Refacto with arr fct ptr
- [ ] OPT default time on libpcap


