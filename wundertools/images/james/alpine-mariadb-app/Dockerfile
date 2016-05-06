#
# Extends the core db image by adding a default database.  The DB will 
# be pre-configured based on build args, which have defaults
#
# Typically use this for access:
#    mysqli://app:app@{DB}/app
#
FROM quay.io/wunder/alpine-mariadb
MAINTAINER docker@wunder.io

# Pull some args from the build command line (or docker-compose build: args: )
ARG MYSQL_ROOT_PASSWORD=root
ARG MYSQL_DATABASE=app
ARG MYSQL_USER=app
ARG MYSQL_PASSWORD=app

# Initial db setup
# - Secure the db, leaving a lame root password, that can be changed in sub images, or in containers
# - Make sure that NOBODY can access the server without a password
# - Kill the anonymous users
# - Kill off the demo database
# - Make our changes take effect
#
# Additionally
# - try to stop the mysql server 
# - remove the mysql client now that we don't need it anymore
# - clean up apk
#
RUN apk --update add mysql-client && \
	(/usr/bin/mysqld_safe --socket=/var/run/mariadb/mariadb.sock &) && sleep 3 && \
    mysql -S /var/run/mariadb/mariadb.sock -u root -e "UPDATE mysql.user SET Password=PASSWORD('${MYSQL_ROOT_PASSWORD}') WHERE User='root'" && \
    mysql -S /var/run/mariadb/mariadb.sock -u root -e "DELETE FROM mysql.user WHERE User=''" && \
    mysql -S /var/run/mariadb/mariadb.sock -u root -e "DROP DATABASE test" && \
    mysql -S /var/run/mariadb/mariadb.sock -u root -e "CREATE DATABASE ${MYSQL_DATABASE}" && \
    mysql -S /var/run/mariadb/mariadb.sock -u root -e "GRANT ALL ON ${MYSQL_DATABASE}.* to ${MYSQL_USER}@'%' IDENTIFIED BY '${MYSQL_PASSWORD}'" && \
    mysql -S /var/run/mariadb/mariadb.sock -u root -e "FLUSH PRIVILEGES" &&\
    killall mysqld && \
    apk del mysql-client && \
    rm -rf /tmp/* && \
    rm -rf /var/cache/apk/* &&\
    sleep 3 # waiting for mysql to die
