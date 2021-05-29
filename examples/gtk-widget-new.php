<?php

//namespace Hello\World;

if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

class MyWidget extends \GtkWidget {
    protected $_scale = 1000;

    /**
     * Put this function to protected to get error message
     * @override GtkWidget::realize
    public function realize(GtkWidget $widget) {
        MyWidget *priv = (MyWidget *)widget;
        //MyCpuPrivate *priv = MY_CPU(widget)->priv;
        GtkAllocation alloc;
        GdkWindowAttr attrs;
        guint attrs_mask;

        gtk_widget_set_realized(widget, TRUE);

        gtk_widget_get_allocation(widget, &alloc);

        attrs.x           = alloc.x;
        attrs.y           = alloc.y;
        attrs.width       = alloc.width;
        attrs.height      = alloc.height;
        attrs.window_type = GDK_WINDOW_CHILD;
        attrs.wclass      = GDK_INPUT_OUTPUT;
        attrs.event_mask  = gtk_widget_get_events(widget) | GDK_EXPOSURE_MASK;

        attrs_mask = GDK_WA_X | GDK_WA_Y;

        priv->window = gdk_window_new(gtk_widget_get_parent_window(widget),
                    &attrs, attrs_mask);
        gdk_window_set_user_data(priv->window, widget);
        gtk_widget_set_window(widget, priv->window);
    }
    */

    /**
     * Put this function to protected to get error message
     * @override GtkWidget::draw
     */
    public function draw(cairo_t $cr):bool {
        //$allocation = new GdkRectangle();
        \gtk_widget_get_allocation($this, $allocation);

        $scaleX = $allocation->width / $this->_scale;
        $scaleY = $allocation->height / $this->_scale;

        // draw the foreground
        cairo_set_source_rgb($cr, 1.0, 0.0, 0.0);
        cairo_move_to($cr, 155.*$scaleX, 165.*$scaleY);
        cairo_line_to($cr, 155.*$scaleX, 838.*$scaleY);
        cairo_line_to($cr, 265.*$scaleX, 900.*$scaleY);
        cairo_line_to($cr, 849.*$scaleX, 564.*$scaleY);
        cairo_line_to($cr, 849.*$scaleX, 438.*$scaleY);
        cairo_line_to($cr, 265.*$scaleX, 100.*$scaleY);
        cairo_line_to($cr, 155.*$scaleX, 165.*$scaleY);
        cairo_move_to($cr, 265.*$scaleX, 100.*$scaleY);
        cairo_line_to($cr, 265.*$scaleX, 652.*$scaleY);
        cairo_line_to($cr, 526.*$scaleX, 502.*$scaleY);
        cairo_move_to($cr, 369.*$scaleX, 411.*$scaleY);
        cairo_line_to($cr, 633.*$scaleX, 564.*$scaleY);
        cairo_move_to($cr, 369.*$scaleX, 286.*$scaleY);
        cairo_line_to($cr, 369.*$scaleX, 592.*$scaleY);
        cairo_move_to($cr, 369.*$scaleX, 286.*$scaleY);
        cairo_line_to($cr, 849.*$scaleX, 564.*$scaleY);
        cairo_move_to($cr, 633.*$scaleX, 564.*$scaleY);
        cairo_line_to($cr, 155.*$scaleX, 838.*$scaleY);
        cairo_stroke($cr);

        return false;
    }
}

function my_callback($object, $param, $user_data){
}

function my_destroy($object, $param, $user_data){
}

function my_notify_title($object, $param, $user_data){
    echo "my_notify_title\n";
    var_dump($object, $param, $user_data);
}

\gtk_init($argc, $argv);


$widget = new MyWidget();
$container = new \GtkContainer();
$bin = new \GtkBin();
$window = new \GtkWindow();

\gtk_container_add($window, $widget);
\gtk_widget_show_all($window);

/*var_dump($widget);
var_dump($container);
var_dump($bin);
var_dump($window);*/

//g_signal_connect($window, "destroy", "\gtk_main_quit", NULL);

\g_object_connect($window, "signal::destroy", "\gtk_main_quit", null
                         , 'notify::title', "my_notify_title", 333
                         , NULL);

\gtk_main();
