<wpd>/
  + php-ext-gtk-build/
  + php-ext-gtk-src/
     + configure

$ mkdir php-ext-gtk-build
$ cd php-ext-gtk-src
$ phpize
$ cd ../php-ext-gtk-build
$ ../php-ext-gtk-src/configure --with-php-config=/home/dev/local/bin/php-config
$ make
$ make test
$ make install

$ ~/local/bin/php -dextension_dir=/home/dev/Projects/gtkphp/php-ext-gtk-build/modules -dextension=gtk.so -m
> -m
> --ri gtk
> --re gtk
> --rz gtk

$ make clean

$ cd ../php-ext-gtk-src
$ phpize --clean

