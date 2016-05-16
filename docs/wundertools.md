# Wunder-Tools 

## Standards


## Layout


````

\wundertools -----------> everything to do with wundertools and docker
  \wundertools ---------> a default script launcher, which can be copied to any PATH folder, and used globally
  \bootstrap -----------> the actual central script handler, which loads settings and hands off to commands

  \wundertools.settings.inc -> one of 2 possible paths for custom settings

  \images --------------> folders where we are keeping ideas on how to manage images (can be used functionally)

  \commands ------------> command script folder
  \commands\{COMMAND} --> Various bash commands that replace typically used tools like drush, docker-compose and composer

  \tools ---------------> Little support applets that you may need (handled by the tool command)
````

## Using the tools

*** RIGHT NOW WE HAVE A SET OF BASH SCRIPTS TO PROTOTYPE BEHAVIOUR.  THESE WILL BE REPLACED IN THE FUTURE

The tools are implemented using a set of bash scripts located in the wundertools commands folder.  These
scripts are not to be run directly but rather through the bootstrap.inc, which loads variables before 
launching the command.
