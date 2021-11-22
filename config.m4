dnl $Id$
dnl config.m4 for extension gtk

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(gtk, for gtk support,
dnl Make sure that the comment is aligned:
dnl [  --with-gtk             Include gtk support])

dnl Otherwise use enable:

PHP_ARG_WITH(gtk, for gtk support,
dnl Make sure that the comment is aligned:
[  --with-gtk              Include gtk support])

dnl --with-gui-gtk=3,Gnome

dnl test PHP_GUI

if test "$PHP_GTK" != "no"; then
  dnl Write more examples of tests here...

  dnl # get library FOO build options from pkg-config output
  dnl AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  dnl AC_MSG_CHECKING(for libfoo)
  dnl if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists foo; then
  dnl   if $PKG_CONFIG foo --atleast-version 1.2.3; then
  dnl     LIBFOO_CFLAGS=`$PKG_CONFIG foo --cflags`
  dnl     LIBFOO_LIBDIR=`$PKG_CONFIG foo --libs`
  dnl     LIBFOO_VERSON=`$PKG_CONFIG foo --modversion`
  dnl     AC_MSG_RESULT(from pkgconfig: version $LIBFOO_VERSON)
  dnl   else
  dnl     AC_MSG_ERROR(system libfoo is too old: version 1.2.3 required)
  dnl   fi
  dnl else
  dnl   AC_MSG_ERROR(pkg-config not found)
  dnl fi
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBDIR, GTK_SHARED_LIBADD)
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)

  dnl # --with-gtk -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/gtk.h"  # you most likely want to change this
  dnl if test -r $PHP_GTK/$SEARCH_FOR; then # path given as parameter
  dnl   GTK_DIR=$PHP_GTK
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for gtk files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       GTK_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$GTK_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the gtk distribution])
  dnl fi

  dnl # --with-gtk -> add include path
  dnl PHP_ADD_INCLUDE($GTK_DIR/include)

  dnl # --with-gtk -> check for lib and symbol presence
  dnl LIBNAME=gtk # you may want to change this
  dnl LIBSYMBOL=gtk # you most likely want to change this

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $GTK_DIR/$PHP_LIBDIR, GTK_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_GTKLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong gtk lib version or lib not found])
  dnl ],[
  dnl   -L$GTK_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(GTK_SHARED_LIBADD)


  if test -z "$PKG_CONFIG"; then
    AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  fi

  if test -x "$PKG_CONFIG"; then

    dnl using pkg-config output
    dnl --with-gtk=3,Gnome,shared
    dnl --with-gtk=Gnome,shared
    dnl --with-gtk=3,shared
    dnl --with-gtk=3,Gnome
    dnl --with-gtk=shared
    dnl --with-gtk=Gnome
    dnl --with-gtk=3
    dnl --with-gtk
    num_arg=0
    num_sep="`echo $PHP_GTK | grep -o , | wc -l`"
    param_1="`echo $PHP_GTK | cut -d, -f1`"
    param_2="`echo $PHP_GTK | cut -d, -f2`"
    param_3="`echo $PHP_GTK | cut -d, -f3`"
    if test -z $param_1; then
        AC_MSG_RESULT("Test if $param_1 is zero")
        num_arg=0
    else
        AC_MSG_RESULT("$num_arg")
        AC_MSG_RESULT("Test sum $num_sep+1")
        num_arg=`expr $num_sep + 1`
        AC_MSG_RESULT("$num_arg")
    fi
    AC_MSG_RESULT("not found $param_1;$param_2;$param_3; $num_arg")

    gtk_version="3"
    gtk_namespace=""
    gtk_shared="shared"

    case $num_arg in
        0) AC_MSG_RESULT("Never reached: param_1=yes by default") ;;
        1)
            case $param_1 in
                0) AC_MSG_ERROR(gtk+ version 0.0 is not supported) ;;
                1) AC_MSG_ERROR(gtk+ version 1.0 is not supported) ;;
                2) AC_MSG_ERROR(gtk+ version 2.0 is not supported) ;;
                3) gtk_version="3" ;;
                4) gtk_version="4" ;;
                5) AC_MSG_ERROR(gtk+ version 5.0 is not supported) ;;
                6) AC_MSG_ERROR(gtk+ version 6.0 is not supported) ;;
                7) AC_MSG_ERROR(gtk+ version 7.0 is not supported) ;;
                8) AC_MSG_ERROR(gtk+ version 8.0 is not supported) ;;
                9) AC_MSG_ERROR(gtk+ version 9.0 is not supported) ;;
                static) gtk_shared="static" ;;
                shared) gtk_shared="shared" ;;
                yes) ;;
                no) ;;
                *) gtk_namespace="$param_1" ;;
            esac
        ;;
        2) AC_MSG_ERROR(TODO 2 parameter passed) ;;
        3)
            case $param_1 in
                3) gtk_version="3" ;;
                4) gtk_version="4" ;;
                *) AC_MSG_ERROR(Invalide Gtk version $param_1) ;;
            esac
            case $param_3 in
                static) gtk_shared="static" ;;
                shared) gtk_shared="shared" ;;
                *) AC_MSG_ERROR(Invalide build type for parameter 3 $param_3) ;;
            esac
            gtk_namespace="$param_2"
        ;;
        *) AC_MSG_ERROR(Invalide parameter count : $num_arg, max : 3) ;;
    esac

    AC_MSG_CHECKING("for gtk+-$gtk_version.0.pc")
    if test "$PHP_GTK" = "yes" -o "$PHP_GTK" = "/usr"; then
      PKNAME=gtk+-3.0
      AC_MSG_RESULT(using default path)
    else
      PKNAME="gtk+-$gtk_version.0"
      AC_MSG_RESULT("using  $PKNAME")
      AC_MSG_WARN(Could not find gtk+-3.0.pc. Try without $PHP_GTK or set PKG_CONFIG_PATH)
    fi
  fi

  if test -n "$PKNAME"; then
    AC_MSG_CHECKING(for gtk+ 3.22.30 or greater)
    if $PKG_CONFIG --atleast-version 3.22.30 $PKNAME; then
      gtk_version_full=`$PKG_CONFIG --modversion $PKNAME`
      AC_MSG_RESULT($gtk_version_full)
    else
      AC_MSG_ERROR(gtk+ version 3.22.30 or later is required to compile php with Gtk+ support)
    fi

    GTK_LIBS=`$PKG_CONFIG --libs   $PKNAME`
    GTK_INCL=`$PKG_CONFIG --cflags $PKNAME`
  fi

  PHP_EVAL_LIBLINE($GTK_LIBS, GTK_SHARED_LIBADD)
  PHP_EVAL_INCLINE($GTK_INCL, GTK_SHARED_LIBADD)

  PHP_ADD_INCLUDE($PHP_GTK)

  PHP_SUBST(GTK_SHARED_LIBADD)

  cairo_sources="php_cairo/cairo.c \
                 php_cairo/status.c \
                 php_cairo/antialias.c \
                 php_cairo/content.c \
                 php_cairo/device-type.c \
                 php_cairo/extend.c \
                 php_cairo/fill-rule.c \
                 php_cairo/filter.c \
                 php_cairo/font-slant.c \
                 php_cairo/font-type.c \
                 php_cairo/font-weight.c \
                 php_cairo/hint-metrics.c \
                 php_cairo/hint-style.c \
                 php_cairo/line-cap.c \
                 php_cairo/line-join.c \
                 php_cairo/operator.c \
                 php_cairo/pattern-type.c \
                 php_cairo/region-overlap.c \
                 php_cairo/subpixel-order.c \
                 php_cairo/surface-type.c \
                 php_cairo/text-cluster-flags.c \
                 php_cairo/rectangle.c \
                 php_cairo/rectangle-int.c \
                 php_cairo/path-data-type.c \
                 php_cairo/path-data.c \
                 php_cairo/path.c \
                 php_cairo/font-options.c \
                 php_cairo/matrix.c \
                 php_cairo/format.c \
                 php_cairo/device.c \
                 php_cairo/font-face.c \
                 php_cairo/font-extents.c \
                 php_cairo/text-cluster.c \
                 php_cairo/text-extents.c \
                 php_cairo/scaled-font.c \
                 php_cairo/pattern.c \
                 php_cairo/ft-synthesize.c \
                 php_cairo/ft.c \
                 php_cairo/glyph.c \
                 php_cairo/region.c \
                 php_cairo/surface.c \
                 php_cairo/transformations.c \
                 php_cairo/image-surface.c \
                 php_cairo/raster-source.c \
                 php_cairo/svg.c \
                 php_cairo/svg-version.c \
                     php_cairo/image-data.c \
                 php_cairo/png.c "


  doc_sources="php_doc/scanner.c \
               php_doc/tag.c \
               php_doc/parameter.c \
               php_doc/value.c \
               php_doc/comment.c "

  glib_sources="php_glib/str.c \
                php_glib/hash-table.c \
                php_glib/list.c \
                php_glib/quark.c \
                php_glib/error.c "

  gobject_sources="php_gobject/object.c \
                   php_gobject/object-extends.c \
                   php_gobject/type.c \
                   php_gobject/value.c \
                   php_gobject/paramspecs.c \
                   php_gobject/signal.c"

  gdk_sources="php_gdk/pixbuf.c \
               php_gdk/rectangle.c "

  gtk_sources="php_gtk/widget.c \
               php_gtk/widget-extends.c \
               php_gtk/requisition.c \
               php_gtk/requested-size.c \
               php_gtk/container.c \
               php_gtk/bin.c \
               php_gtk/box.c \
               php_gtk/window.c \
               php_gtk/button.c \
               php_gtk/main.c "

  sources="gtk.c $cairo_sources $glib_sources $doc_sources $gobject_sources $gdk_sources $gtk_sources"

  ext_ns=$gtk_namespace

  PHP_NEW_EXTENSION(gtk, $sources, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1 -DGTK_NS="$ext_ns")
  PHP_ADD_BUILD_DIR($ext_builddir/php_doc, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/php_cairo, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/php_glib, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/php_gobject, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/php_gdk, 1)
  PHP_ADD_BUILD_DIR($ext_builddir/php_gtk, 1)
  PHP_ADD_MAKEFILE_FRAGMENT()

fi
