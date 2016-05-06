###
# Possibly, we could use a docker target for gulp rendering, based on
# a custom image for the theme.  This image could wrap up everything
# and container the node application required for rendering.
#
# @NOTE there is no wundertools functionality that uses this, it is
#  just some conceptualization that is being worked on
#
FROM quay.io/wunder/alpine-developershell-james

ADD ./ /app/gulptarget
VOLUME /app/gulp_target/node_modules
