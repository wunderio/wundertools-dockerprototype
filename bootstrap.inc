#!/usr/bin/env bash

###
# Bootstrap
#
# The wundertools bootstrap is 3 stages
#
# 1. load custom settings from settings.inc
# 2. fill in any missing settings from default values
# 3. Hand off to a command in the commands folder.
#

# Make all variables shell/env variables (mainly so that docker-compose can see them)
set -a

###########################################
# STAGE 1 : Include the manual settings inc
#
# Put any settings overrides there
#

###
# PATHS : Paths are set during configuration, as they are needed
#   often to find settings files
#

# some commands might want to be able to refer to the active path?
if [ -z "${PATH_EXECUTION}" ]; then
    PATH_EXECUTION="$(pwd)"
fi

###
# PATH_WUNDERTOOLS : the path to the wundertools configuration and utilities
#
if [ -z "${PATH_WUNDERTOOLS}" ]; then
    PATH_WUNDERTOOLS="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
fi


WUNDERTOOLS_SETTINGS_FILENAME="wundertools.settings.inc"
# Include main config
if [ -f "$PATH_WUNDERTOOLS/${WUNDERTOOLS_SETTINGS_FILENAME}" ]; then
  source "$PATH_WUNDERTOOLS/${WUNDERTOOLS_SETTINGS_FILENAME}"
fi

# App project root
#
# PATH_APP : the path to the application root
# SUBPATH_APP : if no PATH_APP is set, this will be used to find PATH_APP from PATH_WUNDERTOOLS

if [ -z "${PATH_APP}" ]; then
  if [ -z "${SUBPATH_APP}" ]; then
    if [ -d "${PATH_WUNDERTOOLS}/app" ]; then
      SUBPATH_APP="app"
    else
      SUBPATH_APP="../"
    fi
  fi

  PATH_APP="$( cd "${PATH_WUNDERTOOLS}" && cd "${SUBPATH_APP}" && pwd )"
fi

# check if there is a config in the app folder
if [ -f "$PATH_APP/${WUNDERTOOLS_SETTINGS_FILENAME}" ]; then
  source "$PATH_APP/${WUNDERTOOLS_SETTINGS_FILENAME}"
fi

# App source root
#
# PATH_SOURCE : the path to the application root
# SUBPATH_APP_SOURCE : if no PATH_SOURCE is set, this will be used to find PATH_SOURCE FROM PATH_APP

if [ -z "${PATH_SOURCE}" ]; then
  if [ -z "${SUBPATH_APP_SOURCE}" ]; then
    PATH_SOURCE="${PATH_APP}"
  else
    PATH_SOURCE="$( cd "${PATH_APP}" && cd "${SUBPATH_APP_SOURCE}" && pwd )"
  fi
fi

# App settings root
#
# PATH_SETTINGS : the path to the settings root
# SUBPATH_APP_SOURCE : if no PATH_SOURCE is set, this will be used to find PATH_SOURCE FROM PATH_APP

if [ -z "${PATH_SETTINGS}" ]; then
  if [ -z "${SUBPATH_APP_SOURCE}" ]; then
    PATH_SETTINGS="${PATH_APP}"
  else
    PATH_SETTINGS="$( cd "${PATH_APP}" && cd "${SUBPATH_APP_SOURCE}" && pwd )"
  fi
fi


###
# THINGS THAT AREN'T ALWAYS WORKING YET
#
# These things will likely require you to manually set them if something breaks
# In general each section here has it's own documentation describing it's issue
#


# nothing here right now



##########################
# STAGE 2 : DEFAULT VALUES
#
# This section tries to autodetermine various values, if they are not
# already manually defined above.
#


if [ ! -f ~/.gitconfig ]; then
  echo ">> creating host user ~/.gitconfig, in which composer may store a github token, if you provide it.We will use a host file for this, so that the github token is persistant, and doesn't need to be re-entered."
  touch ~/.gitconfig
fi

#
# GENERIC
#

# Project name
if [ -z "${PROJECT}" ]; then
    PROJECT="$(basename $(cd ${PATH_WUNDERTOOLS} && cd ../ && pwd))"
fi

# perform some sanity checks on the project name, to make it safe for docker networks and container names
PROJECT="$(echo "${PROJECT}" | tr '[:upper:]' '[:lower:]' | tr -cd '[:alnum:]')"

# Detect the OS in some level because some commands like sed work differently on OS X compared to most Linux distributions.
OS="$(uname)"

#
# DOCKER COMPOSE
#

# Set some vars use by Docker-Compose. This may not be necessary for us.
if [ -z "${COMPOSE_PROJECT_NAME}" ]; then
    COMPOSE_PROJECT_NAME="${PROJECT}"
fi

# Look for a compose file
if [ -z "${COMPOSE_FILE}" ]; then
  if [ -f "${PATH_APP}/docker-compose.yml" ]; then
    COMPOSE_FILE="${PATH_APP}/docker-compose.yml"
  elif [ -f "${PATH_APP}/compose-${PROJECT}.yml" ]; then
    COMPOSE_FILE="${PATH_APP}/compose-${PROJECT}.yml"
  elif [ -f "${PATH_WUNDERTOOLS}/docker-compose.yml" ]; then
    COMPOSE_FILE="${PATH_WUNDERTOOLS}/docker-compose.yml"
  elif [ -f "${PATH_WUNDERTOOLS}/compose-${PROJECT}.yml" ]; then
    COMPOSE_FILE="${PATH_WUNDERTOOLS}/compose-${PROJECT}.yml"
  else
    COMPOSE_FILE="${PATH_WUNDERTOOLS}/compose-default.yml"
  fi
fi

# Here we try to predict what network docker-compose will have created, as
# we will need to know it for some of the commands
if [ -z "${COMPOSE_NETWORK}" ]; then
    COMPOSE_NETWORK="${PROJECT}_default"
fi

# dev image
if [ -z "${DOCKER_IMAGE_DEVELOPERTOOL}" ]; then
  # this is just some old image that I (James) have been using for a while.
    DOCKER_IMAGE_DEVELOPERTOOL="quay.io/wunder/wundertools-image-fuzzy-developershell"
fi

#
# CONTAINER PATHS : what paths are used inside the containers
#
# @note this is new, and I am not sure yet how to split these up
# but really they are only used inside the commands.
#

# Path to user home in the container
if [ -z "${CONTAINER_PATH_HOME}" ]; then
  CONTAINER_PATH_HOME="/app"
fi
# CONTAINER_PATH_APP : root application path inside the images
if [ -z "${CONTAINER_PATH_APP}" ]; then
  CONTAINER_PATH_APP="/app"
fi
# CONTAINER_PATH_SOURCE : root source path inside the images
if [ -z "${CONTAINER_PATH_SOURCE}" ]; then
  CONTAINER_PATH_SOURCE="/app"
fi

#####################################################
# STAGE 3 : determine what command to run, and run it
#
if [ -z "${PATH_COMMANDS}" ]; then
  PATH_COMMANDS="${PATH_WUNDERTOOLS}/commands"
fi

PATH_COMMAND="${PATH_COMMANDS}/$1"

if [ ! -f "${PATH_COMMAND}" ]; then
  PATH_COMMAND="${PATH_COMMANDS}/compose"
else
  shift
fi

#echo "CONFIGURED [PATH_WUNDERTOOLS:${PATH_WUNDERTOOLS}][PATH_APP:${PATH_APP}][PATH_COMMAND:${PATH_COMMAND}][ARGS:$@]"

# Run the command
source "${PATH_COMMAND}" $@
