FROM ilari/alpine-mariadb
MAINTAINER me@me.me

# Pull some args from the build command line (or docker-compose build: args: )
ARG MYSQL_ROOT_PASSWORD
ARG MYSQL_DATABASE
ARG MYSQL_USER
ARG MYSQL_PASSWORD

# Initial db setup
# - Secure the db, leaving a lame root password, that can be changed in sub images, or in containers
# - Make sure that NOBODY can access the server without a password
# - Kill the anonymous users
# - Kill off the demo database
# - Make our changes take effect
RUN apk --update add mysql-client && \
	(/usr/bin/mysqld_safe --socket=/var/run/mariadb/mariadb.sock &) && sleep 1 && \
    mysql -S /var/run/mariadb/mariadb.sock -u root -e "UPDATE mysql.user SET Password=PASSWORD('${MYSQL_ROOT_PASSWORD}') WHERE User='root'" && \
    mysql -S /var/run/mariadb/mariadb.sock -u root -e "DELETE FROM mysql.user WHERE User=''" && \
    mysql -S /var/run/mariadb/mariadb.sock -u root -e "DROP DATABASE test" && \
    mysql -S /var/run/mariadb/mariadb.sock -u root -e "CREATE DATABASE ${MYSQL_DATABASE}" && \
    mysql -S /var/run/mariadb/mariadb.sock -u root -e "GRANT ALL ON ${MYSQL_DATABASE}.* to ${MYSQL_USER}@'%' IDENTIFIED BY '${MYSQL_PASSWORD}'" && \
    mysql -S /var/run/mariadb/mariadb.sock -u root -e "FLUSH PRIVILEGES" &&\
    apk del mysql-client && \
    rm -rf /tmp/* && \
    rm -rf /var/cache/apk/*
