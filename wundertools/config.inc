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
# @NOTE keep this [a-z] and [0-9] for your own sanity
#
#PROJECT="myproject"

###
# Some important paths used in the app.  These are autodetermined by
# default to be ./app and ./wundertools from your root project, but
# I guess that you could override them here.
#
#
#PATH_APP=""
#PATH_WUNDERTOOLS=""

###
# A docker image that can be used for developer shell and commands
# Some of the command scripts use this image to run containers as
# commands; this image provides a base starting point for those
# containers.
# It is easier to maintain a single image for this, although each
# container could of course use it's own image.
#
#DOCKER_IMAGE_DEVELOPERTOOL=""

#######################################
# THINGS THAT AREN'T ALWAYS WORKING YET
#
# These things will likely require you to manually set them if something breaks
# In general each section here has it's own documentation describing it's issue



# nothing here right now



################
# DEFAULT VALUES
#
# This section tries to autodetermine various values, if they are not 
# already manually defined above.
#

#
# PATHS
#

# some commands might want to be able to refer to the active path?
if [ -z "${PATH_EXECUTION}" ]; then
    PATH_EXECUTION="$(pwd)"
fi

# App project root
#
# PATH_APP : the path to the application root
# PATH_WUNDERTOOLS : the path to the wundertools configuration and utilities
#
if [ -z "${PATH_WUNDERTOOLS}" ]; then
    PATH_WUNDERTOOLS="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
fi


SUBPATH_APP="app" # @NOTE THAT IF YOU CHANGE THIS, YOU MIGHT NEED TO CHANGE THE YML FILE BINDS TO MATCH 
if [ -z "${SUBPATH_APP}" ]; then
    SUBPATH_APP="app"
fi
if [ -z "${PATH_APP}" ]; then
    PATH_APP="$( cd "$( dirname "${PATH_WUNDERTOOLS}" )" && pwd )/${SUBPATH_APP}"
fi

if [ ! -f ~/.gitconfig ]; then
  echo ">> creating host user ~/.gitconfig, in which composer may store a github token, if you provide it.We will use a host file for this, so that the github token is persistant, and doesn't need to be re-entered."
  touch ~/.gitconfig
fi

#
# GENERIC
#

# Project name
if [ -z "${PROJECT}" ]; then
    PROJECT="$(basename $(cd ${PATH_APP} && cd ../ && pwd))"
fi

# perform some sanity checks on the project name, to make it safe for docker networks and container names
PROJECT="${PROJECT,,}" # lower case
PROJECT="$(echo "${PROJECT}" | tr '[:upper:]' '[:lower:]' | tr -cd '[:alnum:]')"

#
# DOCKER COMPOSE
#

# dev image
if [ -z "${DOCKER_IMAGE_DEVELOPERTOOL}" ]; then
	# this is just some old image that I (James) have been using for a while.
    DOCKER_IMAGE_DEVELOPERTOOL="quay.io/wunder/wundertools-image-fuzzy-developershell"
fi

# Set some vars use by Docker-Compose. This may not be necessary for us.
export COMPOSE_PROJECT_NAME="${PROJECT}"
export COMPOSE_FILE="${PATH_WUNDERTOOLS}/compose-default.yml"

if [ -z "${COMPOSE_NETWORK}" ]; then
    COMPOSE_NETWORK="${PROJECT}_default"
fi
