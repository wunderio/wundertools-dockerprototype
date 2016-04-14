# Wunder-Tools 

## Getting set up

- Install Docker locally:
  - OS X / Windows
    - If you have an invite for Docker for Mac / Docker for Windows, use that.
    - In the meantime, get Docker Toolbox from here https://www.docker.com/products/docker-toolbox
  - Linux
    - See https://docs.docker.com/engine/installation
- Clone this repository.
- (if using Docker Toolbox) Open the docker Quickstart Terminal.
- Run `docker-compose up` in the project root.

### DNS

#### Current quick and dirty solution:

- Run `docker ps` and get the name of the web service container
- Run `docker inspect --format '{{ .NetworkSettings.IPAddress }}' <CONTAINER_NAME>` (where `<CONTAINER_NAME>` is the name of the container from the previous step). This will give you the IP address of the container.
- Add an entry to `/etc/hosts` with `<CONTAINER_IP> wunderdemo.local.wunder.io`

This approach is evil, we know it and we'll fix it once Docker for Mac/Windows is out of private beta.

#### Longer term solution
We are considering playing with DNS Dock: https://github.com/tonistiigi/dnsdock, but at the moment this doesn't work reliably on OS X with boot2docker.

Using this approach will require that you run a container on your machine that runs DNS, and then you tell you host to use it as a DNS server

##### DNSDOCK with docker-machine

You will need to run DNSDOCk and attach the dns service to the docker-machine IP

    $/> docker run --detach=true --volume=/var/run/docker.sock:/var/run/docker.sock --name=dnsdock --publish=$(docker-machine ip default):53:53/udp tonistiigi/dnsdock