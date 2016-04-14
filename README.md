# Wunder-Tools 

## Getting set up

### DNS

  *DNS is an open topic

Currently we are considering playing with DNS Dock: https://github.com/tonistiigi/dnsdock

Using this approach will require that you run a container on your machine that runs DNS, and then you tell you host to use it as a DNS server

#### DNSDOCK with docker-machine

You will need to run DNSDOCk and attach the dns service to the docker-machine IP

    $/> docker run --detach=true --volume=/var/run/docker.sock:/var/run/docker.sock --name=dnsdock --publish=$(docker-machine ip default):53:53/udp tonistiigi/dnsdock