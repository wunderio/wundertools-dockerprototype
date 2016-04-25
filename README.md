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
to the docker subnet (bad host) and so a manual route may be necessary

#### DNSDOCK

Currently we are considering playing with DNS Dock: 
https://github.com/tonistiigi/dnsdock

Using this approach will require that you run a container on your machine that 
runs DNS, and then you tell you host to use it as a DNS server

#### DNSDOCK with docker-machine

You will need to run DNSDOCk and attach the dns service to the docker-machine IP

    $/> docker run --detach=true --volume=/var/run/docker.sock:/var/run/docker.sock --name=dnsdock --publish=$(docker-machine ip default):53:53/udp tonistiigi/dnsdock
