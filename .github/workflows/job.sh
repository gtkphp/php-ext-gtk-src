#!/bin/sh

pwd

sudo apt-get update
sudo apt-get install libgtk-3-dev

apt-cach search valgrind
sudo apt-get install valgrind

cd ..
git clone https://github.com/php/php-src.git
mkdir php-build
cd php-src
git checkout PHP-7.2.24
./buildconf
cd ../php-build
../php-src/configure --disable-all --with-gtk --enable-debug --prefix=/home/runner/work/php-ext-gtk-src
make -j8


cd ../php-ext-gtk-src

phpize

mkdir ../php-ext-gtk-release
cd ../php-ext-gtk-release
../php-ext-gtk-src/configure --with-gtk

build_result=0
make -j4 || build_result=1

#php -dextension_dir=./modules -dextension=gtk.so ../php-ext-gtk-src/examples/g-hash-table-new.php

export TRAVIS=1
export TEST_PHP_ARGS="tests/ -m --html /home/runner/work/php-ext-gtk-src/report.html"
make test
cat /home/runner/work/php-ext-gtk-src/report.html
ls /home/runner/work/php-ext-gtk-src
echo "Result of make is : $build_result"
echo "Result of make is : ?"
/home/runner/work/php-ext-gtk-src/php-build/sapi/cli/php --version

