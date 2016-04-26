#!/bin/sh

SOCK=/var/run/mariadb/mariadb.sock

export PATH=/bin:/usr/bin

/usr/bin/mysqld_safe --socket="$SOCK" --console &
sleep 3

# Initial db setup
# - Secure the db, leaving a lame root password, that can be changed in sub images, or in containers
# - Make sure that NOBODY can access the server without a password
# - Kill the anonymous users
# - Kill off the demo database
# - Make our changes take effect

echo "Executing SQL"
mysql -S "$SOCK" -u root <<SQL
UPDATE mysql.user SET Password=PASSWORD('${MYSQL_ROOT_PASSWORD}') WHERE User='root';
DELETE FROM mysql.user WHERE User='';
DROP DATABASE test;
CREATE DATABASE ${MYSQL_DATABASE};
GRANT ALL ON ${MYSQL_DATABASE}.* to ${MYSQL_USER}@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
FLUSH PRIVILEGES;
SQL

# end the show gracefully
killall -TERM mysqld
sleep 5
