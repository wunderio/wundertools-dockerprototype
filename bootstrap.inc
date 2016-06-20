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

###
# Include the utilities inc
#
source "${PATH_WUNDERTOOLS}/utility.inc"

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
  if [ -z "${SUBPATH_APP_SETTINGS}" ]; then
    PATH_SETTINGS="${PATH_SOURCE}"
  else
    PATH_SETTINGS="$( cd "${PATH_APP}" && cd "${SUBPATH_APP_SETTINGS}" && pwd )"
  fi
fi

# App source web root
#
# PATH_WEBROOT : the path to the application web root
# SUBPATH_APP_WEBROOT : if no PATH_WEBROOT is set, this will be used to find PATH_WEBROOT FROM PATH_APP

if [ -z "${PATH_WEBROOT}" ]; then
  if [ -z "${SUBPATH_APP_WEBROOT}" ]; then
    PATH_WEBROOT="${PATH_SOURCE}/web"
  else
    PATH_WEBROOT="$( cd "${PATH_APP}" && cd "${SUBPATH_APP_WEBROOT}" && pwd )"
  fi
fi

# Assets root
#
# PATH_ASSETS : the path to the assets root
# SUBPATH_APP_ASSETS : if no PATH_ASSETS is set, this will be used to find PATH_ASSETS FROM PATH_APP

if [ -z "${PATH_ASSETS}" ]; then
  if [ -z "${SUBPATH_APP_ASSETS}" ]; then
    PATH_ASSETS="${PATH_APP}/assets"
  else
    PATH_ASSETS="$( cd "${PATH_APP}" && cd "${SUBPATH_APP_ASSETS}" && pwd )"
  fi
fi

# Data root
#
# PATH_DATA : the path to the DATA root
# SUBPATH_APP_DATA : if no PATH_DATA is set, this will be used to find PATH_DATA FROM PATH_APP

if [ -z "${PATH_DATA}" ]; then
  if [ -z "${SUBPATH_APP_DATA}" ]; then
    PATH_DATA="${PATH_APP}/DATA"
  else
    PATH_DATA="$( cd "${PATH_APP}" && cd "${SUBPATH_APP_DATA}" && pwd )"
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
  CONTAINER_PATH_APP="${CONTAINER_PATH_HOME}"
fi
# CONTAINER_PATH_SOURCE : root source path inside the images
if [ -z "${CONTAINER_PATH_SOURCE}" ]; then
  CONTAINER_PATH_SOURCE="${CONTAINER_PATH_APP}"
fi
# CONTAINER_PATH_WEBROOT : root source path inside the images
if [ -z "${CONTAINER_PATH_WEBROOT}" ]; then
  CONTAINER_PATH_WEBROOT="${CONTAINER_PATH_SOURCE}/web"
fi
# CONTAINER_PATH_VENDOR : vendor source path inside the images
if [ -z "${CONTAINER_PATH_VENDOR}" ]; then
  CONTAINER_PATH_VENDOR="${CONTAINER_PATH_APP}/vendor"
fi
# CONTAINER_PATH_SETTINGS : settings path inside the images
if [ -z "${CONTAINER_PATH_SETTINGS}" ]; then
  CONTAINER_PATH_SETTINGS="${CONTAINER_PATH_HOME}"
fi

#####################################################
# STAGE 3 : determine what command to run, and run it
#
if [ -z "${PATH_COMMANDS}" ]; then
  PATH_COMMANDS="${PATH_WUNDERTOOLS}/commands"
fi

COMMAND="$1"

# If you pass a command boostrap, then no command is run
if [ "$COMMAND" == "bootstrap" ]; then
  echo "-== wundertools bootstrapped ==-"
else

  PATH_COMMAND="${PATH_COMMANDS}/$1"

  if [ ! -f "${PATH_COMMAND}" ]; then
    PATH_COMMAND="${PATH_COMMANDS}/compose"
  else
    shift
  fi

  #echo "CONFIGURED [PATH_WUNDERTOOLS:${PATH_WUNDERTOOLS}][PATH_APP:${PATH_APP}][PATH_COMMAND:${PATH_COMMAND}][ARGS:$@]"

  # Run the command
  source "${PATH_COMMAND}" $@

fi