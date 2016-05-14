# Wunder-Tools behavioural prototype

This project is a simple behavoural prototype, to see what we would want from a docker based tool.

This is not a complete docker toolset, and is not designed for easy implementation.  If you want
to use this tool, expect to have to learn somethings about docker and docker-composer, as most of
the effort here is simple wrappers around docker-compose, and docker run.

Suggested reading:

- (Docker CLI)[]
- (Docker Run reference)[]
- (Docker Compose reference)[]
- (Docker composer YML reference)[]

* Honestly, if the tools doesn't work for you, but you aren't willing to understand docker and docker-composer
then you are not likely to get much support.

## Issues

If you have any issues or suggestions, feel free to use the github issue tracker

## Layout

@TODO new layout


## Documentation

There is extensive documentation on the wundertools approach in /wundertools/docs

## Getting set up

#### I have a project I want to use with wundertools

This tool can be integrated into an existing D8 project by putting
the contents if this repository into your D8 root, and naming it 
"wundertools"

    $/> git clone {repository url} wundertools

##### You are expected to have

A drupal 8 source root, as per the drupal-composer project, with a root path with a 
web and vendor folder.  The root should have the following elements

The web services will require the following paths:

 - web -----------> folder container drupal web root (index.php)
 - vendor --------> folder in which composer dependencies are

With these elements you should be able to get a web response, if you have 
your vendor dependencies installed.  If you don't have vendor filled in, then
you will need some of the following items

##### Additional elements

If you want to run tool commands, you will want to have the following additional
elements, which will be mapped into containers

###### composer 

~/.ssh -----------> gets used for git
~/.gitconfig -----> gets used for git

###### drush

~/.ssh -----------> get's used with remote drush
/drush -----------> get's mapped as though it were ~/.drush

###### Drupal Console

~/.ssh -----------> get's used with remote drush
/drush -----------> get's mapped as though it were ~/.drush
/console ---------> get's mapped as though it were ~/.console

#### I want to test/demo wundertools

@TODO

### Next steps

Then you should be up and running.  See "access my site"

For more commands See "Using the tools"

## Using the tools

The tools are implemented using a set of bash scripts located in the wundertools folder.  These
scripts are to be run directly.  The scripts assume that the layout is respected.

Each of the commands should be run directly, from the project root and should try to pull in the 
configuration from config.inc automatically.

If you get sick of running relative path commands, consider copying ./wundertools/wundertools to any user bin path, to allow you to run "$/> wundertools {command}" instead of "$/> ./wundertools/{command}"

Get more information by looking in the wundertools/docs

### Accessing my containers

#### Container IP

You can usually rely on a direct route to your container.  To find the IP for any container:

    $/> wundertools/tools/containerIP www

*** Note that on some docker setups, the host has not routed container traffic 
to the docker subnet (bad host) and so a manual route may be necessary.  The OSX Beta client seems to have this issue, but no route seems avaialable.

#### Container shell

You can get a fast shell inside any of the actual containers using: 

    $/> wundertools/tools/execshell fpm

*** Note that this shell is not as usefull as the featured shell from "wundertools/shell" as most of the service images do not even have bash installed.

