# CUSTOM MARIADB IMAGE

this image build is here as an example of how we built our DB image,
and to allow a custom image to be built as a part of your project.

You may want to have a custom image, so that you can control DB
access credentials, and DB name.

## TO use this

You have to options to use this build:

1. manage the build manually yourself,
2. include the build as a part of your docker-compose yml file, and have it built automatically.

It is generally advised to use (1.) instead of (2.) if you are considering
using your build in production.  For a production service, you want your
compose yml file to be able to stand alone, with no additional files needed,
and so you want to build your own image, and distribute it using docker,
and a private repository.

### Manual build

in the folder that containers the Dockerfile:

    $/> docker build --tag=MyImageName .

This will build the image.  Consider using a repository based name
such as "quay.io/MyQuayUser/MyProject_DBImage" if you plan on
distributing the image with docker push.

You can push the image:

    $/> docker push quay.io/MyQuayUser/MyProject_DBImage

# Better image management:

This is the simplest approach to building images. You can also 
consider a much more sophisticated make process, as is used 
by Ragnar K (WKEE), and is also included in this repository.
