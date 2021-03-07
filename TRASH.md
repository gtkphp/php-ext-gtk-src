config.m4

PKG_CONFIG_PATH="" && configure --with-gtk=Gnome\Gtk,4

```
define([GTK_HELP_TEXT],[[
             ^  ^-------- Use the Gtk+ version installed on your systeme.
             |              - version can be one of: 2, 3, 4.
             +----------- Associate the gtk extension with the namespace of your choice.
                            - ns can be any valide PHP namespace.
                          Exemple, use Gtk+3 with "Gnome" namespace:
                            --with-gtk=Gnome,3
                          Exemple, use Gtk+2 without namespace:
                            --with-gtk=,2]])

PHP_ARG_WITH(gtk, for gtk support,
dnl Make sure that the comment is aligned:
[  --with-gtk=ns,version  Include gtk support]GTK_HELP_TEXT)

ext_ns="`echo $PHP_GTK | cut -d, -f1`"
gtk_version="`echo $PHP_GTK | cut -d, -f2`"

PHP_NEW_EXTENSION(gtk, gtk.c $glib_sources $g_sources, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1 -DGTK_NS="\\\"$ext_ns\\\"")
```
refactor `if test "$PHP_GTK" = "yes"`
