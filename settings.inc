#!/usr/bin/env bash

######################
# MANUAL CONFIGURATION
#
# Here lies manual configrations which you would probably want to
# base in a config format using yml or json. 
#
# We should move this to a central config format as soon as possible
# to keep such configuration outside of a wundertools concept, so
# the application layout stays generic, instead of wundertools specific.
#

####
# Project name
#
# This is primarily used as the root name for all containers and
# images that the system will build.  By default it uses the project
# root path basename, but you can use this to override it.
#
# @NOTE keep this [a-z] and [0-9] for your own sanity, all other 
#   characters will be stripped out anyway, to make it behave
#   predictable with docker-compose
#
#PROJECT="myproject"

###
# Some important paths used in the app.  These are autodetermined by
# default to be ./app and ./wundertools from your root project, but
# I guess that you could override them here.
#

# Set the path to the Wundertools root folder
#PATH_WUNDERTOOLS=""

# Set the path to the root of your project
#PATH_APP=""
# Instead of PATH_APP, you could set the relative path from PATH_WUNDERTOOLS to PATH_APP
#SUBPATH_APP=""

###
# Docker compose config
#
# Different vars to configure just the docker-compose stuff
#

# Configure what project name get's used with docker-compose
# (defaults to $PROJECT)
#COMPOSE_PROJECT_NAME=""

# Configure what compose yml file gets used.
# By default the following are checked in this order:
# - PATH_APP/docker-compose.yml
# - PATH_APP/compose-$PROJECT.yml
# - PATH_WUNDERTOOLS/docker-compose.yml
# - PATH_WUNDERTOOLS/compose-$PROJECT.yml
# - PATH_WUNDERTOOLS/compose-default.yml
#
#COMPOSE_FILE=""

# Configure what network name command containers should use
#
# Usually it looks like "$PROJECT_default", but it could be 
# something else if you have a custom yml file
#

# Set the network name
#COMPOSE_NETWORK=""
# Just set the network suffix
#COMPOSE_NETWORK_SUFFIX=""

###
# A docker image that can be used for developer shell and commands
# Some of the command scripts use this image to run containers as
# commands; this image provides a base starting point for those
# containers.
# It is easier to maintain a single image for this, although each
# container could of course use it's own image.
#
#DOCKER_IMAGE_DEVELOPERTOOL=""
