<?php

declare(strict_types=0);
//declare(fatal_warnings=1);


if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', '1');
ini_set('display_startup_errors', '1');
error_reporting(E_ALL);


//echo cairo_status_to_string(CAIRO_STATUS_NO_MEMORY);

$square = 30;
$height = $square*2;
$width = $square*2;
$format = CAIRO_FORMAT_ARGB32;
$stride = cairo_format_stride_for_width ($format, $width);

$data = "";
$init_red=false;
$use_red=0;

for($j=0; $j<$height; $j++) {
    if($j%$square==0) {
        $init_red = !$init_red;
        $use_red = $init_red;
    }
    for($i=0; $i<$width; $i++) {
        if($i%$square==0) $use_red = !$use_red;
        if ($use_red) $data .= "\x00\x00\xFF\xFF";// red
        else $data .= "\xFF\x00\x00\xFF";// blue
    }
}


$surface = cairo_image_surface_create ($format, 250, 80);
$cr = cairo_create ($surface);

$image = cairo_image_surface_create_for_data ($data, CAIRO_FORMAT_ARGB32, $width, $height, $stride);

cairo_set_source_surface ($cr, $image, 0, 0);
cairo_paint ($cr);

$status = cairo_surface_write_to_png($surface, "/home/dev/Projects/gtkphp/hello.png");

echo strlen(cairo_image_surface_get_data ($image)).PHP_EOL;
echo cairo_image_surface_get_height ($image).PHP_EOL;
echo cairo_image_surface_get_width ($image).PHP_EOL;
echo cairo_image_surface_get_stride ($image).PHP_EOL;


/*
$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);
cairo_move_to($cr, 1.0, 0.0);
cairo_line_to($cr, 21.0, 20.0);
cairo_set_source_rgb ($cr, 0, 0, 0);
cairo_stroke ($cr);
$status = cairo_surface_write_to_png($surface, "/home/dev/Projects/gtkphp/hello.png");
*/




/*
$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);


cairo_move_to ($cr, 10.0, 10.0);

cairo_text_path($cr, "Hello World");

cairo_set_source_rgb ($cr, 0, 0, 0);
cairo_fill ($cr);

$status = cairo_surface_write_to_png($surface, "/home/dev/Projects/gtkphp/hello.png");

echo cairo_status_to_string($status);

cairo_reference($cr);

cairo_surface_destroy($surface);
cairo_destroy($cr);
*/



// Cairo Matrix


/*
$a = new cairo_matrix_t();

$xx = &$a->xx;

$matrix = new cairo_matrix_t();
$a = new cairo_matrix_t();
$b = new cairo_matrix_t();
$xx = &$a->xx;

cairo_matrix_init_identity($a);
var_dump($a);
cairo_matrix_scale($a, 2.0, 2.0);
var_dump($a);
cairo_matrix_init_identity($b);
cairo_matrix_multiply($matrix, $a, $b);

$matrix->xx += 0.5;
$matrix->x0 = 5;
var_dump($matrix);
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
