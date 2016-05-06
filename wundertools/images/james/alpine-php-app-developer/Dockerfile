# DEVELOPER PHP IMAGE
#
# This images extends the base php image by enabled a few developer oriented
# extensions and increasing some of the PHP settings for memorry etc.  Also the
# php status and ping paths are enabled at /phpfpm-status and /phpfpm-ping
#
# This image maintains low error verbosity in http response, as it is felt that
# developers can rely on the container output.
#
FROM quay.io/wunder/alpine-php
MAINTAINER docker@wunder.io

RUN apk --update add php7-xdebug

####
# Override nginx configuration for Drupal site
#
# override default php-fpm include conf
ADD etc/php7/php-fpm.d/www.conf /etc/php7/php-fpm.d/www.conf
# override xdebug settings
ADD etc/php7/conf.d/xdebug.ini /etc/php7/conf.d/xdebug.ini
