# Wunder-Tools 

## Layout

*** note that our app folder is modeled on the drupal8 for composer

````
\app -------------------> everything to do with your application
  \drush ---------------> .drush folder for container user, which can hold aliases and cache
  \console -------------> .console fodler for container user, which can hold everything from $/> drupal init

  \vendor --------------> folder that has elements managed by drupal composer

\wundertools -----------> everything to do with wundertools and docker
  \docker --------------> folders per image build for custom project images (each contains a Dockerfile)

  \config.inc ----------> A special include script that configs variables for commands

  \COMMAND -------------> Various bash commands that replace typically used tools like drush, docker-compose and composer

  \tools ---------------> Little support applets that you may need
````

## Using the tools

*** RIGHT NOW WE HAVE A SET OF BASH SCRIPTS TO PROTOTYPE BEHAVIOUR.  THESE WILL BE REPLACED

The tools are implemented using a set of bash scripts located in the wundertools folder.  These
scripts are to be run directly.  The scripts assume that the layout is respected.

Each of the commands should be run directly, from the project root and should pull in the configuration from config.inc

### compose : docker-compose replacement

Here we wrap docker compose so that we can hard code the project name, and perhaps the project network
settings.  This also allows us to get the docker-compose.yml out of the project root folder.

#### example

```
# start all of the needed containers 
$/> wundertools/composer up -d
# start all of the needed containers but keep attached to them for debugging 
$/> wundertools/composer up
# stop all container
$/> wundertools/composer down
# stop all containers and remove them
$/> wundertools/composer down -v

# find out more
$/> wundertools/composer --help
```

### composer : wraps PHP composer into a command container

This command container acts as through it were running composer from the project
root.  Pass compose command and flags directly to the command

#### example

    $/> wundertools/composer update
    $/> wundertools/composer install

### drush : wraps drush into a command container

You can use this command as a replacement for running drush  from the host, and
pass drush flags directly to the script

#### example

````
$/> wundertools/drush cc all
$/> wundertools/drush sql-cli
````

### drupal : wraps drupal console into a command container


#### example

````
$/> wundertools/drush config:import
$/> wundertools/drush cache:rebuild all
$/> wundertools/drush generate:module
````

### shell : gives a usefull ZSH shell with access to toolS and other containers

This is a command container, that provides a full shell, similar to what you
would want from an ssh shell.

#### example

````
# open a zsh shell:
$/> wundertools/shell
# run a direct command
$/> wundertools/shell ls -la

## Getting set up

The project comes completely un-built.  Building may require docker steps as 
well as other steps related to Drupal architecture.

To start all of the pieces for docker use the compose command, which behaves 
similar to vagrant:

    $/> wundertools/compose up -d 


Typically you will need to run composer:

    $/> wundertools/composer update
    $/> wundertools/composer upgrade

Then you should be up and running.

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
