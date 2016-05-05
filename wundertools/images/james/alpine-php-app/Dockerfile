#####
# Extends the core php image
#
# @TODO use these https://github.com/wunderkraut/docker-container-app-configs/tree/master/php
#    When ther are fixed.
#
FROM quay.io/wunder/alpine-php
MAINTAINER docker@wunder.io

####
# Add a www php-fpm service definition
#
ADD etc/php7/php-fpm.d/www.conf /etc/php7/php-fpm.d/www.conf

###
# Correct entrypoint
ENTRYPOINT ["/usr/sbin/php-fpm7", "--nodaemonize"]