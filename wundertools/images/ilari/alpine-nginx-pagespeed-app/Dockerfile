FROM ilari/alpine-nginx-pagespeed
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

# Override the default nginx.conf
#   - modify the default server
#   - allow it to get take any url
#   - switch the root path to /app/project
#   - configure for Drupal http response
#   - use fpm.app for fastcgi-pass URL
#   - log to stdout (listen for logs at the container)
ADD etc/nginx/conf.d/drupal.conf /etc/nginx/conf.d/drupal.conf
