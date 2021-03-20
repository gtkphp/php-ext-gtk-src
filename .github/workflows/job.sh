#!/bin/sh

pwd

sudo apt-get update
sudo apt-get install libgtk-3-dev

phpize

mkdir ../php-ext-gtk-release
cd ../php-ext-gtk-release
../php-ext-gtk-src/configure --with-gtk

build_result=$(make -j4)
echo "Result of make is : $build_result"

#php -dextension_dir=./modules -dextension=gtk.so ../php-ext-gtk-src/examples/g-hash-table-new.php

export TRAVIS=1
export TEST_PHP_ARGS="tests/ -m --html /home/runner/work/php-ext-gtk-src/report.html"
make test
