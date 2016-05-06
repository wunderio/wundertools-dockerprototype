# APP NGINX IMAGE
#
FROM quay.io/wunder/alpine-nginx-pagespeed
MAINTAINER docker@wunder.io

####
# Use drupal specific confs
#
# Get confs from https://github.com/wunderkraut/docker-container-app-configs
#
# Currently the following issues exist upstream:
#   - nginx_drupal.conf should be app_drupal.conf
#   - ssl nginx: [emerg] "keepalive_timeout" directive is duplicate in /etc/nginx/conf.d/nginx_server_ssl.conf:16
#
RUN mkdir /etc/nginx/conf.d && \
    wget -O /etc/nginx/nginx.conf https://raw.githubusercontent.com/wunderkraut/docker-container-app-configs/master/nginx/nginx.conf_drupal && \
    wget -O /etc/nginx/conf.d/app_drupal.conf https://raw.githubusercontent.com/wunderkraut/docker-container-app-configs/master/nginx/conf.d/nginx_drupal.conf && \
    wget -P /etc/nginx/conf.d https://raw.githubusercontent.com/wunderkraut/docker-container-app-configs/master/nginx/conf.d/fastcgi_drupal.conf && \
    wget -P /etc/nginx/conf.d https://raw.githubusercontent.com/wunderkraut/docker-container-app-configs/master/nginx/conf.d/nginx_app.conf && \
    wget -P /etc/nginx/conf.d https://raw.githubusercontent.com/wunderkraut/docker-container-app-configs/master/nginx/conf.d/nginx_upstream.conf
