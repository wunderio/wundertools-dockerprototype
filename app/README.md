# /app

This folder will contain all project specific code.

## Source Code

Solutions for getting source code here:

1. git clone / git submodule
2. add it to this git repo

## Contents of this folder

The Layout of the app folder is expected to be like this:

./project        -> actual drupal8 compose template root
./project/vendor -> the composer vendor folder that composer creates
./project/web    -> web root for nginx/fpm

./settings       -> a top level folder for configuration of project tools
./drush          -> drush configuration folder (mapped in as ~/.drush)
