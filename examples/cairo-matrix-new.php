<?php

declare(strict_types=0);
//declare(fatal_warnings=1);


if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', '1');
ini_set('display_startup_errors', '1');
error_reporting(E_ALL);


/*
$rect = new cairo_rectangle_t();//0.0, 0.0, 0.0, 0.0
$rect->x = 10.0;
$rect->y = 20.0;
$rect->width = 110.0;
$rect->height = 90.0;
var_dump($rect);
//print_r((array)$rect);
//print_r($rect);

//$r = GdkRectangle::__set_state((array)$rect);
//var_dump($b);
*/


/* */
$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

cairo_move_to ($cr, 10.0, 10.0);

cairo_text_path($cr, "Hello World");

cairo_set_source_rgb ($cr, 0, 0, 0);
cairo_fill ($cr);

$status = cairo_surface_write_to_png($surface, "/home/dev/Projects/gtkphp/hello.png");

echo cairo_status_to_string($status);

/*
cairo_reference($cr);

cairo_surface_destroy($surface);
cairo_destroy($cr);
*/



/*
$matrix = new cairo_matrix_t();

cairo_matrix_init_identity($matrix);

var_dump($matrix);

require_once("Cairo.php");
use Cairo\Matrix;

$matrix = new Matrix;
//$matrix->initIdentity();
$matrix->xx = M_PI;
$matrix['xx'] = "3.14";

var_dump($matrix);
*/




/*
$matrix = new cairo_matrix_t;
cairo_matrix_init_identity($matrix);
cairo_matrix_init($matrix, "3.14kg", 0.0, 0.0, 0.0, 0.0, 0.0);

var_dump($matrix);
*/



/*

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

cairo_move_to ($cr, 64.0, 25.6);
cairo_rel_line_to ($cr, 51.2, 51.2);
cairo_rel_line_to ($cr, -51.2, 51.2);
cairo_rel_line_to ($cr, -51.2, -51.2);
cairo_close_path ($cr);

cairo_set_line_width ($cr, 10.0);
cairo_set_source_rgb ($cr, 0, 0, 1);
cairo_fill_preserve ($cr);
cairo_set_source_rgb ($cr, 0, 0, 0);
cairo_stroke ($cr);


$status = cairo_surface_write_to_png($surface, "tutprog_hello.png");


*/

/*
//$surface = new cairo_surface_t();
$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

cairo_move_to ($cr, 64.0, 25.6);
cairo_rectangle ($cr, 0.0, 0.0, 21.0, 29.7);

cairo_set_source_rgb ($cr, 1.0, 0.0, 1.0);
cairo_fill ($cr);

$status = cairo_surface_write_to_png($surface, "/home/dev/Projects/gtkphp/hello.png");

var_dump($status);
var_dump($surface);
var_dump($cr);
*/

/*
$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

//cairo_move_to ($cr, 64.0, 25.6);
cairo_rectangle ($cr, 0.0, 0.0, 21.0, 29.7);

$path = cairo_copy_path ($cr);
*/


/*
for ($i=0; $i < $path->num_data; $i += $path->data[i]->header->length) {
    switch (path->data[$i]->header->type) {
    case CAIRO_PATH_MOVE_TO:
        g_print("CAIRO_PATH_MOVE_TO\n");
        //do_move_to_things ($path->data[$i+1]->point->x, $path->data[$i+1]->point->y);
        break;
    }
}
*/

/*
var_dump($path->data[0]->header);
var_dump($path->data[0]->header->type);
var_dump($path->data[1]->point->x);
var_dump($path);

var_dump($surface);
var_dump($cr);

$path_data = new cairo_path_data_t(CAIRO_PATH_MOVE_TO);
var_dump($path_data);
*/

/*
$path_data = new cairo_path_data_t(3.14, 1.62);
$path_data->x = 3.32;
var_dump($path_data);
*/

/*
$path = cairo_copy_path_flat($cr);
var_dump($path);
*/


