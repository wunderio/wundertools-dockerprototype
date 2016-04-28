FROM ilari/alpine-php
MAINTAINER me@me.me

####
# Some Wundertools standards
#

# /app is our common application root
RUN mkdir /app

# create two users:
RUN /usr/sbin/addgroup -g 1000 app && \
    /usr/sbin/adduser -D -H -h /app -u 1000 -G app app && \
    /bin/chown -R app:app /app && \
    /usr/sbin/addgroup -g 500 service && \
    /usr/sbin/adduser -D -H -u 500 -G service service && \
	/usr/sbin/adduser service app

####
# Override nginx configuration for Drupal site

# override default php-fpm include conf
#  - switch service user to use "service"
#  - use tcp socket for listening.
#  - log output to stdout (listen for logs at the container)
#  - increase memory to 256M
ADD etc/php7/php-fpm.d/www.conf /etc/php7/php-fpm.d/www.conf
