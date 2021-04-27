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
     * @override GtkWidget::draw
     */
    public function draw(cairo_t $cr):bool {
        /*
        \gtk_widget_get_allocation($this, $allocation);
        $scaleX = $allocation->width / $this->_scale;
        $scaleY = $allocation->height / $this->_scale;

        // draw the foreground
        cairo_set_source_rgb($cr, 0.0, 1.0, 0.0);
        cairo_move_to($cr, 155.*$scale_x, 165.*$scale_y);
        cairo_line_to($cr, 155.*$scale_x, 838.*$scale_y);
        cairo_line_to($cr, 265.*$scale_x, 900.*$scale_y);
        cairo_line_to($cr, 849.*$scale_x, 564.*$scale_y);
        cairo_line_to($cr, 849.*$scale_x, 438.*$scale_y);
        cairo_line_to($cr, 265.*$scale_x, 100.*$scale_y);
        cairo_line_to($cr, 155.*$scale_x, 165.*$scale_y);
        cairo_move_to($cr, 265.*$scale_x, 100.*$scale_y);
        cairo_line_to($cr, 265.*$scale_x, 652.*$scale_y);
        cairo_line_to($cr, 526.*$scale_x, 502.*$scale_y);
        cairo_move_to($cr, 369.*$scale_x, 411.*$scale_y);
        cairo_line_to($cr, 633.*$scale_x, 564.*$scale_y);
        cairo_move_to($cr, 369.*$scale_x, 286.*$scale_y);
        cairo_line_to($cr, 369.*$scale_x, 592.*$scale_y);
        cairo_move_to($cr, 369.*$scale_x, 286.*$scale_y);
        cairo_line_to($cr, 849.*$scale_x, 564.*$scale_y);
        cairo_move_to($cr, 633.*$scale_x, 564.*$scale_y);
        cairo_line_to($cr, 155.*$scale_x, 838.*$scale_y);
        cairo_stroke($cr);
        */
        cairo_set_source_rgb($cr, 1.0, 0.0, 0.0);
        cairo_rectangle($cr, 5.0, 2.0, 70.0, 85.0);
        cairo_fill($cr);

        //cairo_translate(cr, 0, 7);
        //cairo_set_source_rgb(cr, 0, 0, 0);
        //cairo_paint(cr);
        $limit = 20 -      50                / 5;
        for ($i = 1; $i <= 20; $i++) {

           if ($i > $limit) {
              cairo_set_source_rgb($cr, 0.6, 1.0, 0);
           } else {
              cairo_set_source_rgb($cr, 0.2, 0.4, 0);
           }

           cairo_rectangle($cr, 8,  $i * 4, 30, 3);
           cairo_rectangle($cr, 42, $i * 4, 30, 3);
           cairo_fill($cr);
        }

        return false;
    }
}

function my_callback($object, $param, $user_data){
}

function my_destroy($object, $param, $user_data){
}

\gtk_init($argc, $argv);




$req = new GtkRequestedSize();
var_dump($req);

$widget = new MyWidget();
$container = new \GtkContainer();
$bin = new \GtkBin();
$window = new \GtkWindow();

\gtk_container_add($window, $widget);
\gtk_widget_show_all($window);


var_dump($widget);
var_dump($container);
var_dump($bin);
var_dump($window);

\g_signal_connect($window, "destroy", "\gtk_main_quit", NULL);

\gtk_main();
