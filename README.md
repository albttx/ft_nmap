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

## Build

You can simply build the project with `make`,
you might have missing header on OS X, in that case i recommend you to build the project with docker

#### With Docker

```
# Build image nmap and nmap-dev
make build

# Run bash in the image (dev mode)
make run-dev

# Run nmap in the container
$ docker run --rm --tty nmap --help
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


