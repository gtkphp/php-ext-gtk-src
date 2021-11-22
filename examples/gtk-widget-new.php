<?php

//namespace My;

if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

define('g_signal_new_id', 0);

class MyWidget extends \GtkWidget {
    protected $_scale = 1000;
    private GdkWindow $window;

    /**
     * @g_signal_new("changed",
     *               MyWidget::class,
     *               G_SIGNAL_RUN_LAST, NULL,
     *               NULL, NULL,
     *               G_TYPE_INT, 1, G_TYPE_INT)
     *
     */
    const CHANGED = g_signal_new_id;


    /** @g_override GtkWidgetClass.realize
    public function realize(GtkWidget $widget) {
        //MyWidget *priv = (MyWidget *)widget;
        //MyCpuPrivate *priv = MY_CPU(widget)->priv;
        //GtkAllocation $alloc;
        $attrs=new GdkWindowAttr();
        echo 'What appended'.PHP_EOL;
        $attrs_mask=0;

        gtk_widget_set_realized($widget, TRUE);

        gtk_widget_get_allocation($widget, $alloc);// alloc is a reference

        $attrs->x           = $alloc->x;
        $attrs->y           = $alloc->y;
        $attrs->width       = $alloc->width;
        $attrs->height      = $alloc->height;
        $attrs->window_type = GDK_WINDOW_CHILD;
        $attrs->wclass      = GDK_INPUT_OUTPUT;
        $attrs->event_mask  = gtk_widget_get_events($widget) | GDK_EXPOSURE_MASK;

        $attrs_mask = GDK_WA_X | GDK_WA_Y;

        $widget->window = gdk_window_new(gtk_widget_get_parent_window($widget),
                    $attrs, $attrs_mask);
        gdk_window_set_user_data($widget->window, $widget);
        gtk_widget_set_window($widget, $widget->window);
    } */

    /** @g_override GtkWidgetClass.draw */
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

class SuperWidget extends MyWidget {
}

function my_callback($object, $param, $user_data){
}

function my_destroy($object, $param, $user_data){
}

function my_notify_title($object, $param, $user_data){
    echo "my_notify_title\n";
    //var_dump($object, $param, $user_data);
}

function my_notify_widget($object, $param, $user_data):int{
    echo "my_notify_widget(".get_class($object).", ".$param.", ".$user_data.")\n";
    return 1.3;
}

class OtherWidget extends \GtkWidget {
}


/*
gtk_init($argc, $argv);
$widget = new MyWidget();
var_dump($widget);

$other = new OtherWidget();
var_dump($other);

$o = new MyWidget();
var_dump($o);

//$c = new GtkContainer();
//var_dump($c);

$s = new SuperWidget();
var_dump($s);
*/


//new GtkWidget(); Abstract


//$container = new \GtkContainer();
//$bin = new \GtkBin();

/**/
gtk_init($argc, $argv);

$widget = new MyWidget();
//$widget = new GtkButton();
//gtk_button_set_image($button, $widget);
$window = new GtkWindow();

gtk_container_add($window, $widget);
gtk_widget_show($widget);
gtk_widget_show($window);

//var_dump($widget);
//var_dump($container);
//var_dump($bin);
//var_dump($window);


g_object_connect($window, "signal::destroy", "\gtk_main_quit", null
                        //, 'signal::notify::title', "my_notify_title", 333
                        , NULL);
/*
g_signal_connect($widget, "changed", "my_notify_widget", 555);

g_signal_emit_by_name($widget, "changed", 11, $ret);
var_dump($ret);
*/

gtk_main();
