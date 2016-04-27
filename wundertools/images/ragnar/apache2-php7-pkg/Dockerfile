FROM debian:jessie
MAINTAINER ragnar@waalaskala.com

RUN DEBIAN_FRONTEND=noninteractive apt-get update
# install apt-utils as early as possible to prevent further nagging
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y apt-utils

# install early, some basic container inspection tools
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y less
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y vim

RUN DEBIAN_FRONTEND=noninteractive apt-get install -y wget
RUN echo "deb http://packages.dotdeb.org jessie all" >> /etc/apt/sources.list
RUN echo "deb-src http://packages.dotdeb.org jessie all" >> /etc/apt/sources.list
RUN wget "https://www.dotdeb.org/dotdeb.gpg"
RUN apt-key add dotdeb.gpg
RUN rm dotdeb.gpg
RUN DEBIAN_FRONTEND=noninteractive apt-get update

RUN DEBIAN_FRONTEND=noninteractive apt-get upgrade -y
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y apache2
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y php7.0
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y php7.0-curl
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y php7.0-gd
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y php7.0-mysql

# for pecl extensions
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y php7.0-dev
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y php-pear

# send out emails from php
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y ssmtp

# cleanup
RUN DEBIAN_FRONTEND=noninteractive apt-get clean
RUN rm -rf /var/lib/apt/lists/*
