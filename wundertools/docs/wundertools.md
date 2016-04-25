# Wunder-Tools 

## Standards


## Layout


````
\app -------------------> everything to do with your application


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

Each of the commands should be run directly, from the project root and should try to pull in the 
configuration from config.inc automatically.

#### The following information and management commands exist

* config : just a quick script to output the configuration values
* compose : docker-compose wrapper


### Accessing my containers

@TODO
