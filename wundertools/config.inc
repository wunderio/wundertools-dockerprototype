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
#
PROJECT=""

###
# Some important paths used in the app.  These are autodetermined by
# default to be ./app and ./wundertools from your root project, but
# I guess that you could override them here.
#
PATH_APP=""
PATH_WUNDERTOOLS=""

###
# A docker image that can be used for developer shell and commands
# Some of the command scripts use this image to run containers as
# commands; this image provides a base starting point for those
# containers.
# The default image is an old centos build, with various php-cli
# extensions, composer, gulp and zsh installed.
# It is easier to maintain a single image for this, although each
# container could of course use it's own image.
#
DOCKER_IMAGE_DEVELOPERTOOL="jamesnesbitt/wunder-developershell"

#######################################
# THINGS THAT AREN'T ALWAYS WORKING YET
#
# These things will likely require you to manually set them if something breaks
# In general each section here has it's own documentation describing it's issue


#
# Networking id and bridge problem.
#
# ERROR: docker: Error response from daemon: network {SOMETHING}_default not found.
# SHORT ANSWER: try setting this: COMPOSE_NETWORK="bridge"
# LONG ANSWER: do "docker inspect $CONTAINER" on one of your containers and look for "Networks": {"{NETWORK}"
#
#COMPOSE_NETWORK="bridge"  # this makes docker-compose use the shared docker network interface


####################
# DEFAULT VALUES
#
# This section tries to autodetermine various values, if they are not 
# already manually defined above.
#

# App project root
#
# PATH_APP : the path to the application root
# PATH_WUNDERTOOLS : the path to the wundertools configuration and utilities
#
if [ -z "${PATH_WUNDERTOOLS}" ]; then
    PATH_WUNDERTOOLS="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
fi
if [ -z "${PATH_APP}" ]; then
    PATH_APP="$( cd "$( dirname "${PATH_WUNDERTOOLS}" )" && pwd )/app"
fi

if [ ! -f ~/.gitconfig ]; then
  echo ">> creating host user ~/.gitconfig, in which composer may store a github token, if you provide it.We will use a host file for this, so that the github token is persistant, and doesn't need to be re-entered."
  touch ~/.gitconfig
fi


# Project name
if [ -z "${PROJECT}" ]; then
    PROJECT="$(basename ${PATH_APP})"
fi

# dev image
if [ -z "${DOCKER_IMAGE_DEVELOPERTOOL}" ]; then
	# this is just some old image that I (James) have been using for a while.
    DOCKER_IMAGE_DEVELOPERTOOL="jamesnesbitt/wunder-developershell"
fi

# Set some vars use by Docker-Compose. This may not be necessary for us.
export COMPOSE_PROJECT_NAME="${PROJECT}"
export COMPOSE_FILE="${PATH_WUNDERTOOLS}/compose-default.yml"

if [ -z "${COMPOSE_NETWORK}" ]; then
    COMPOSE_NETWORK="${PROJECT}_default"
fi
