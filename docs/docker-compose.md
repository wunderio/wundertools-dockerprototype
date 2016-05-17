# Docker-Compose on Wundertools

We decided to try to rely on docker-compose for container management.

- docker-compose is a docker supported tool, that is becoming an industrial standard
- docker-compose uses a yml syntax file that is supported by other tools
- all we need to rely on is the yml config (the tool is irrelevant)

## YML file

We look for the yml file in the following places:

 Compose yml file is looked for here (PATH_APP is usually ./app or ../)

1. PATH_APP/compose.{PROJECT}.yml
2. PATH_APP/compose.default.yml
3. ./compose.{PROJECT}.yml
4. ./compose.default.yml
