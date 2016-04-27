FROM apache2-php7-pkg
MAINTAINER ragnar@waalaskala.com

RUN install -o root -g root -m 755 -d /app
RUN install -o root -g root -m 755 -d /logs

RUN a2enmod rewrite
RUN a2enmod expires
RUN a2enmod headers

RUN a2dissite 000-default

ENV APACHE_RUN_USER www-data
ENV APACHE_RUN_GROUP www-data
ENV APACHE_LOG_DIR /logs/apache2

ENV APACHE_LOCK_DIR /run/lock/apache2
ENV APACHE_PID_FILE /run/apache2/pid

WORKDIR /data

CMD [ "/usr/sbin/apache2", "-D", "FOREGROUND" ]
