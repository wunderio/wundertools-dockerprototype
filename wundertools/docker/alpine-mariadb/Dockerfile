FROM ilari/alpine-mariadb
MAINTAINER me@me.me

ARG MYSQL_ROOT_PASSWORD
ARG MYSQL_DATABASE
ARG MYSQL_USER
ARG MYSQL_PASSWORD

RUN apk --update add mysql-client

# basic setup
COPY setup.sh /tmp/setup.sh
RUN /tmp/setup.sh
RUN rm /tmp/setup.sh

# cleanup
RUN apk del mysql-client
RUN rm -rf /tmp/*
RUN rm -rf /var/cache/apk/*
