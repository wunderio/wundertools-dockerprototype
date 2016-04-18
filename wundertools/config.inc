#!/usr/bin/env bash

######################
# MANUAL CONFIGURATION

# Project name as used to create containers
PROJECT=""

# Some important paths used
PATH_APP=""
PATH_WUNDERTOOLS=""

# A docker image that can be used for developer shell and commands
DOCKER_IMAGE_DEVELOPERTOOL="jamesnesbitt/wunder-developershell"

#######################################
# THINGS THAT AREN'T ALWAYS WORKING YET
#
# these things will likely require you to manually set them if something breaks
# , so here are some examples"

# ERROR: docker: Error response from daemon: network {SOMETHING}_default not found.
# SHORT ANSWER: try setting this: COMPOSE_NETWORK="bridge"
# LONG ANSWER: do "docker inspect $CONTAINER" on one of your containers and look for "Networks": {"{NETWORK}"
COMPOSE_NETWORK="bridge"

####################
# AUTO DETERMINATION

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
    DOCKER_IMAGE_DEVELOPERTOOL="jamesnesbitt/wunder-developershell"
fi

# Set some vars use by Docker-Compose
export COMPOSE_PROJECT_NAME="${PROJECT}"
export COMPOSE_FILE="${PATH_WUNDERTOOLS}/docker-compose.yml"

if [ -z "${COMPOSE_NETWORK}" ]; then
    COMPOSE_NETWORK="${PROJECT}_default"
fi