# Wunder-Tools behavioural prototype

This project is a simple behavoural prototype, to see what we would want from a docker based tool.

This is not a complete docker toolset, and is not designed for easy implementation.  If you want
to use this tool, expect to have to learn somethings about docker and docker-composer, as most of
the effort here is simple wrappers around docker-compose, and docker run.

Suggested reading:

- [Docker CLI](https://docs.docker.com/engine/reference/commandline/cli/)
- [Docker Run reference](https://docs.docker.com/engine/reference/run/)
- [Docker Compose reference](https://docs.docker.com/compose/gettingstarted/)
- [Docker composer YML reference](https://docs.docker.com/compose/compose-file/)

Honestly, if the tools doesn't work for you, but you aren't willing to understand docker and docker-composer
then you are not likely to get much support.

## Quick start/demo

See a video of the demo:

[![WunderTools Docker prototype demo 22.05.2016](https://img.youtube.com/vi/uDG7ngDdn1Q/0.jpg)](https://youtu.be/uDG7ngDdn1Q)

or if you want a fast start to a new project using this tool or you want to demo the functionality, follow these steps:

- Create a new local folder or a repository for the project.
- In this new folder clone wundertools-dockerprototype to wundertools folder:
~~~
git clone https://github.com/wunderkraut/wundertools-dockerprototype.git wundertools
~~~
or in a real project you should add wundertools-dockerprototype as a submodule like so:
~~~
git submodule add https://github.com/wunderkraut/wundertools-dockerprototype.git wundertools
~~~
- Initialise a new Drupal 8 project with wundertools-dockerprototype from the project root:
~~~
./wundertools/wundertools init
~~~
- Star the containers:
~~~
./wundertools/wundertools up -d
~~~
- Access Drupal 8 installation at http://localhost:8080

## Issues

If you have any issues or suggestions, feel free to use the github [issue tracker](https://github.com/wunderkraut/wundertools-dockerprototype/issues)

## Layout

The original application layout included a wundertools folder (the actual tool) and an app folder (the D8 application on which this tool acted.)  This layout was replaced in version 0.2

The current layout expects that you will clone/export this tool as a folder called "wundertools" in the root of your application.  The tool will then be usable anywhere in the root of your application, and can reference any file in the application root.

````
{wundertools} --------------------> tool root, expected to be named "wundertools"
  \ boostrap.inc -----------------> actual script handler, loads settings and hands off to command
  \ wundertools.settings.inc -----> bash settings, easily readable place to put variables (one of the places)
  \ wundertools ------------------> a nicely named launcher, which can be put anywhere on your host.
                                    (Looks for wundertools/bootstrap)

  \ commands ---------------------> all commands are in this folder
     \ {COMMAND} -----------------> each command gets its own script file
  \ tools ------------------------> less functional commands are called tools, and kept here
     \ {TOOL} --------------------> each tool gets its own script file (launched using the tool command)

  \ images -----------------------> we have packaged some image builds here as examples, which can be used if you want
     \ {USER} --------------------> users who contributed images grouped them here
       \ {IMAGE} -----------------> each image gets its own folder, most likely with a Dockerfile

  \ docs -------------------------> various docs in markdown are kept here
    \ {DOC} ----------------------> each doc gets its own markdown file

````

## Documentation

There is extensive documentation on the wundertools approach in [/wundertools/docs](https://github.com/wunderkraut/wundertools-dockerprototype/tree/master/docs)

## Getting set up

#### I have a project I want to use with wundertools

This tool can be integrated into an existing D8 project by putting
the contents if this repository into your D8 root, and naming it
"wundertools"

    $/> git clone {repository url} wundertools

Now you will have the wundertools folder in your project root, which
can be used to manipulate a number of docker containers and run
some commands.
Some of these commands required that the docker containers are
already started, so that they can be conntected to.

##### Tool install

All commands go through the wundertools/wundertools script, but you
can move that script anywhere on your host, and can use the same
script for any application with a wundertools folder.

If you have "~/bin" in your PATH:

    $/> cp wundertools/wundertools ~/bin/wundertools

Or maybe:

    $/> cp wundertools/wundertools /usr/local/bin/wundertools

Alternatively, you can just alias the script

    $/> alias wundertools="path/to/project/wundertools/wundertools"

###### Examples

These examples assume that you can call the tool globally.  If
you are using the tool in place, remember that you need to call
./wundertools/wundertools

####### To bring your system up - and stay attached to container output

    $/> wundertools up

###### to bring up your system, and get your prompt back

    $/> wundertools up -d

###### to stop all containers

    $/> wundertools stop

###### to (stop and) remove all containers

    $/> wundertools down

*** there are many more commands available to run composer, drush, drupal-console
and to get a zsh shell attached to all of the containers.  See the docs for details

##### You are expected to have

A drupal 8 source root, as per the drupal-composer project, with a root path with a
web and vendor folder.  The root should have the following elements

The web services will require the following paths:

````
e - web -----------> folder container drupal web root (index.php)
 - vendor --------> folder in which composer dependencies are
````

With these elements you should be able to get a web response, if you have
your vendor dependencies installed.  If you don't have vendor filled in, then
you will need some of the following items

##### Additional elements

If you want to run tool commands, you will want to have the following additional
elements, which will be mapped into containers

###### composer

````
~/.ssh -----------> gets used for git
~/.gitconfig -----> gets used for git
````

###### drush

````
~/.ssh -----------> get's used with remote drush
/drush -----------> get's mapped as though it were ~/.drush
````

###### Drupal Console

````
~/.ssh -----------> get's used with remote drush
/drush -----------> get's mapped as though it were ~/.drush
/console ---------> get's mapped as though it were ~/.console
````

#### I want to test/demo wundertools

This application comes with a "demo mode", which is an command called "init", which will
download a drupal 8 project into a subfolder called "app".  This replicates the original
application behaviour

    $/> wundertools init

### Next steps

Then you should be up and running.  See "access my site"

For more commands See "Using wundertoolstools"

## Using wundertools

The tools are implemented using a set of bash scripts located in the wundertools folder.  These
scripts are to be run directly.  The scripts assume that the layout is respected.

Each of the commands should be run directly, from the project root and should try to pull in the
configuration from config.inc automatically.

If you get sick of running relative path commands, consider copying ./wundertools/wundertools to any user bin path, to allow you to run the command
from any path, without worrying about your path to the script.

Get more information by looking in the wundertools/docs

### Accessing my containers

There are various ways the users tend to want to interact with their containers.

- http browser access
- ssh shell access
- mysql direct access
- composer / drush / drupal-console

Some of these are not necessary with this tool (ssh), some are provided as commands, and some require the container IP

#### Container IP

You can usually rely on a direct route to your container.  To find the IP for any container:

    $/> wundertools tools containerIP www

*** Note that on some docker setups, the host has not routed container traffic
to the docker subnet (bad host) and so a manual route may be necessary.  The OSX Beta client seems to have this issue, but no route seems avaialable.

#### Running Drush / Console / Composer

Each of these commands have their own wundertools command.  See the commands documentation for
more information.

Here are some examples

    $/> wundertools drupal generate:content:entity
    $/> wundertools drush cc all
    $/> wundertools composer update

#### Container shell

If you want a ZSH powershell, that is similar to ssh into a virtual machine, consider using the
shell command.  It will give you a shell prompt, ready with composer, git, archivers, drush and
console, as well as npm/nodejs and gulp/grunt ... and many more.  This shell has socket access
to all of the other containers, vi urls: db.app, fpm.app, www.app etc.

You can run the shell to get commands:

    $/> wundertools shell gulp monitor

Or open a full operational prompt:

    $/> wundertools shell

If you really need access to a specific container, you can get a fast shell inside any of the
actual containers using:

    $/> wundertools tools execshell fpm

*** Note that this shell is not as usefull as the featured shell from "wundertools shell" as most of the service images do not even have bash installed.
