IMAGE = alpine-mariadb

build: conf.database conf.user conf.root.pass conf.user.pass
	docker \
		build \
		--build-arg "MYSQL_ROOT_PASSWORD=$(shell cat conf.root.pass)" \
		--build-arg "MYSQL_DATABASE=$(shell cat conf.database)" \
		--build-arg "MYSQL_USER=$(shell cat conf.user)" \
		--build-arg "MYSQL_PASSWORD=$(shell cat conf.user.pass)" \
		-t "$(IMAGE)" \
		.

rmi:
	-docker rmi $(IMAGE)

clean:
	docker images --filter "dangling=true" -q | xargs -r docker rmi
	rm -f conf.*

conf.user:
	read -p "Username: " data && echo "$$data" > "$@"

conf.database:
	read -p "Database: " data && echo "$$data" > "$@"

conf.user.pass:
	pwgen -s 20 1 > "$@"

conf.root.pass:
	pwgen -s 20 1 > "$@"
