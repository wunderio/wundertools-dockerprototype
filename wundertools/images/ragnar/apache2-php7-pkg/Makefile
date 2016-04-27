IMAGE = $(shell basename "$$PWD")

build:
	docker build -t $(IMAGE) .

build_nocache:
	docker build --no-cache=true -t $(IMAGE) .

rmi:
	-docker rmi $(IMAGE)

clean: rmi
	docker ps -a --filter status="exited" --format '{{.ID}}' | xargs -r docker rm
	docker images --filter "dangling=true" -q | xargs -r docker rmi
