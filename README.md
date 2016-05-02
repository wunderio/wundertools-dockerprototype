# Wunder-Tools 

## Layout

*** note that our app folder is modeled on the drupal8 for composer

````
\app -------------------> everything to do with your application
  \drush ---------------> .drush folder for container user, which can hold aliases and cache
  \console -------------> .console folder for container user, which can hold everything from $/> drupal init

  \vendor --------------> folder that has elements managed by drupal composer
  \web -----------------> web server root

\wundertools -----------> everything to do with wundertools and docker
  (see the wundertools/docs/wundertools.md file for more information)

````

## Documentation

There is extensive documentation on the wundertools approach in /wundertools/docs

## Getting set up

The project comes completely un-built.  Building may require docker steps as 
well as other steps related to Drupal architecture.

To start all of the pieces for docker use the compose command, which behaves 
similar to vagrant:

    $/> wundertools/compose up -d 

Typically you will need to run composer:

    $/> wundertools/composer update
    $/> wundertools/composer upgrade

Then you should be up and running.  See "access my site"

For more commands See "Using the tools"

## Using the tools

*** RIGHT NOW WE HAVE A SET OF BASH SCRIPTS TO PROTOTYPE BEHAVIOUR.  THESE WILL BE REPLACED

The tools are implemented using a set of bash scripts located in the wundertools folder.  These
scripts are to be run directly.  The scripts assume that the layout is respected.

Each of the commands should be run directly, from the project root and should try to pull in the 
configuration from config.inc automatically.

If you get sick of running relative path commands, consider copying ./wundertools/wundertools to any user bin path, to allow you to run "$/> wundertools {command}" instead of "$/> ./wundertools/{command}"

Get more information by looking in the wundertools/docs

### Accessing my containers

@TODO

### DNS

*** DNS is an open topic that we have not resolved. Consider just using host 
file entries for now.

#### /etc/hosts

You can usually rely on a direct route to your container.  To find the IP for any container:

    $/> wundertools/tools/containerIP www

*** Note that on some docker setups, the host has not routed container traffic 
to the docker subnet (bad host) and so a manual route may be necessary.  The OSX Beta client seems to have this issue, but no route seems avaialable.

#### DNSDOCK

Currently we are considering playing with DNS Dock: 
https://github.com/tonistiigi/dnsdock

### DNS

#### Current quick and dirty solution:

- Run `docker ps` and get the name of the web service container
- Run  "./wundertools/tool/containerIP www" to find you container IP (or Run `docker inspect --format '{{ .NetworkSettings.IPAddress }}' <CONTAINER_NAME>` (where `<CONTAINER_NAME>` is the name of the container from the previous step). This will give you the IP address of the container.)
- Add an entry to `/etc/hosts` with `<CONTAINER_IP> wunderdemo.local.wunder.io`

This approach is not great, we know it and we'll fix it once Docker for Mac/Windows is out of private beta.  The advantage of this approach is the it means that this tool does not have to manage your OSX network at all, so it won't break it.

#### Longer term solution

We are considering playing with DNS Dock: https://github.com/tonistiigi/dnsdock, but at the moment this doesn't work reliably on OS X with boot2docker.

Using this approach will require that you run a container on your machine that 
runs DNS, and then you tell you host to use it as a DNS server

##### DNSDOCK with docker-machine

You will need to run DNSDOCk and attach the dns service to the docker-machine IP

    $/> docker run --detach=true --volume=/var/run/docker.sock:/var/run/docker.sock --name=dnsdock --publish=$(docker-machine ip default):53:53/udp tonistiigi/dnsdock
