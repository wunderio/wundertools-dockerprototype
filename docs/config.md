# wundertools configuration

As wundertools is a collection of bash scripts, it is configured by use of 
bash or environment variables.  The boostrap tries to include the following
paths to look for custom settings:

  ${PATH_APP}/wundertools.settings.inc     <-- PATH_APP defaults to ./app or ../ (if ./app doesn't exist)
  ./wundertools/wundertools.settings.inc

## Manual settings

Any of the variables used in the app, and whatever custom vars you like, can
be put into your settings.inc.  These will be made available for any command 
and can also be used in the docker-compose.yml.

## Automatic defaults

The bootstrap handler has processes in it that set defaults for any variable
not set.
