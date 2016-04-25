# Command scripts


### The following command tools exist:

* composer : php composer wrapper
* drush : drush wrapper (requires compose is run first)
* drupal : drupal-console wrapper (requires compose is run first)
* shell : a zsh shell prompt, similar to what ssh might give you

### The following are on our @TODO list:

* archive/restore : methods that could be used to backup, which would reuse things like drush
* feature/branch : create running branched environments


## compose : docker-compose replacement

Here we wrap docker compose so that we can hard code the project name, and perhaps the project network
settings.  This also allows us to get the docker-compose.yml out of the project root folder.

### example

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

## composer : wraps PHP composer into a command container

This command container acts as through it were running composer from the project
root.  Pass compose command and flags directly to the command

### example

````
$/> wundertools/composer update
$/> wundertools/composer install
````

## drush : wraps drush into a command container

You can use this command as a replacement for running drush  from the host, and
pass drush flags directly to the script

*** this wrapper uses the drush that comes from the composer update (must run composer first)

### example

````
$/> wundertools/drush cc all
$/> wundertools/drush sql-cli
````

## drupal : wraps drupal console into a command container

This script wraps around the drupal-console.

*** this wrapper uses the console that comes from the composer update (must run composer first)

### example

````
$/> wundertools/drupal config:import
$/> wundertools/drupal cache:rebuild all
$/> wundertools/drupal generate:module
````

## shell : gives a usefull ZSH shell with access to toolS and other containers

This is a command container, that provides a full shell, similar to what you
would want from an ssh shell.

Shell as a command is quite usefull for people who are used to getting ssh access
to a virtual machine, but also because it is quite easy for different developers
and developer teams to customize the image used for their own tastes and needs.
This customization could be done without affecting the project as it fits into
production workflow.

### example

````
# open a zsh shell:
$/> wundertools/shell
# run a direct command
$/> wundertools/shell ls -la
````
