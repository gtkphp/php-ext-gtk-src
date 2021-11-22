<?php

declare(strict_types=0);
//declare(fatal_warnings=1);


if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', '1');
ini_set('display_startup_errors', '1');
error_reporting(E_ALL);


//echo cairo_status_to_string(CAIRO_STATUS_NO_MEMORY);


//$data = new cairo_image_data_t;

/*
$output = "/home/dev/Projects/gtkphp/php-src/ext/gtk/tests/php_cairo/sqaure-output.png";
$input  = "/home/dev/Projects/gtkphp/php-src/ext/gtk/tests/php_cairo/sqaure.png";
$surface = cairo_image_surface_create_from_png ($input);

$image = cairo_image_surface_get_data ($surface);
$image[0] = "\xFF";
$image[1] = "\xFF";
$image[2] = "\x00";


$status = cairo_surface_write_to_png($surface, $output);
*/

/*
$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$device = cairo_surface_get_device($surface);
var_dump($device);

$ref = cairo_device_reference($device);
var_dump($ref);

$status = cairo_device_status($device);
var_dump($status==CAIRO_STATUS_NULL_POINTER);

$input  = "/home/dev/Projects/gtkphp/php-src/ext/gtk/tests/php_cairo/sqaure.png";
$target = cairo_image_surface_create_from_png ($input);
$cr = cairo_create ($target);
$device = cairo_surface_get_device($target);
$status = cairo_device_status($device);
var_dump($status==CAIRO_STATUS_NULL_POINTER);
$type = cairo_device_get_type($device);
var_dump($type==CAIRO_DEVICE_TYPE_INVALID);
$ref = cairo_device_get_reference_count($device);
var_dump($ref==0);
//$ns = cairo_device_observer_elapsed($device);
//var_dump($ns);


$font_options = cairo_font_options_create();
cairo_surface_get_font_options($target, $font_options);
var_dump($font_options);
*/

//confirm_gtk_compiled("");



/*
$quark = g_quark_from_string("Hello");
$string = g_quark_to_string($quark);
var_dump($string);

$error = g_error_new_literal($quark, 30, "The message 0: Hello");
var_dump($error);


$quark = g_quark_from_string("My");
$error = g_error_new($quark, 30, "The message %d: %s", 3, "Hello");

var_dump($error);



$quark = g_quark_from_string("My");
$error = g_error_new_valist($quark, 30, "The message %d: %s", [3, "Hello"]);

var_dump($error);

$ret = g_error_matches($error, g_quark_from_string("My"), 30);
var_dump(true==$ret);



g_set_error($error, g_quark_from_string("My"), 30, "New Message: %s", "ok");
var_dump($error);


g_set_error_literal($error, g_quark_from_string("My"), 30, "New Message: Cool");
var_dump($error);

$err = new GError();
g_propagate_error($err, $error);
var_dump($err);
*/



/*
$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

cairo_translate ($cr, 10, 20);

$x=5.0;
$y=3.0;
cairo_user_to_device_distance($cr, $x, $y);

var_dump($x, $y);
*/

/*
//$options = new cairo_font_options_t;
$options = cairo_font_options_create ();
$other = cairo_font_options_copy($options);
var_dump($options);
var_dump($other);
$status = cairo_font_options_status($options);
var_dump($status==CAIRO_STATUS_SUCCESS);
$status = cairo_font_options_status($other);
var_dump($status==CAIRO_STATUS_SUCCESS);

cairo_font_options_merge($options, $other);


cairo_font_options_set_antialias ($options, CAIRO_ANTIALIAS_GRAY);
$antialias = cairo_font_options_get_antialias ($options);
var_dump($antialias==CAIRO_ANTIALIAS_GRAY);
echo '->'.cairo_font_options_hash($options).PHP_EOL;

cairo_font_options_set_subpixel_order($options, CAIRO_SUBPIXEL_ORDER_RGB);
$subpixel_order = cairo_font_options_get_subpixel_order($options);
var_dump($subpixel_order==CAIRO_SUBPIXEL_ORDER_RGB);

cairo_font_options_set_hint_style($options, CAIRO_HINT_STYLE_MEDIUM);
$hint_style = cairo_font_options_get_hint_style($options);
var_dump($hint_style==CAIRO_HINT_STYLE_MEDIUM);


cairo_font_options_set_hint_metrics($options, CAIRO_HINT_METRICS_ON);
$hint_metrics = cairo_font_options_get_hint_metrics($options);
var_dump($hint_metrics==CAIRO_HINT_METRICS_ON);

if (CAIRO_VERSION >= 11600) {
    cairo_font_options_set_variations($options, "abc");
    $font_variations = cairo_font_options_get_variations($options);
    var_dump($font_variations);
}

echo cairo_font_options_hash($options).PHP_EOL;
echo cairo_font_options_hash($other).PHP_EOL;

$ret = cairo_font_options_equal($options, $other);
var_dump($ret);
*/

/*
$input = __DIR__."/../tests/php_cairo/sqaure.png";
$input = "/home/dev/Projects/gtkphp/php-src/ext/gtk/tests/php_cairo/sqaure.png";
$surface = cairo_image_surface_create_from_png ($input);

$width = cairo_image_surface_get_width($surface);
$height = cairo_image_surface_get_height($surface);
//$taget = cairo_surface_create_similar($surface, CAIRO_CONTENT_COLOR_ALPHA, $width, $height);
$taget = cairo_surface_create_similar_image($surface, CAIRO_FORMAT_ARGB32, $width, $height);


$status = cairo_surface_write_to_png($taget, "/home/dev/Projects/gtkphp/hello.png");

//$image = cairo_image_surface_get_data ($surface);
//var_dump($image);
*/


/*
$square = 30;
$height = $square*2;
$width = $square*2;
$format = CAIRO_FORMAT_ARGB32;
$stride = cairo_format_stride_for_width ($format, $width);

$data = new cairo_image_data_t;
$init_red=false;
$use_red=0;

for($j=0; $j<$height; $j++) {
    if($j%$square==0) {
        $init_red = !$init_red;
        $use_red = $init_red;
    }
    for($i=0; $i<$width; $i++) {
        if($i%$square==0) $use_red = !$use_red;
        if ($use_red) {
            // red
            $data[] = "\x00";
            $data[] = "\x00";
            $data[] = "\xFF";
            $data[] = "\xFF";
        } else {
            // blue
            $data[] = "\xFF";
            $data[] = "\x00";
            $data[] = "\x00";
            $data[] = "\xFF";
        }
    }
}
//var_dump($data);

$surface = cairo_image_surface_create ($format, 250, 80);
$cr = cairo_create ($surface);

$image = cairo_image_surface_create_for_data ($data, CAIRO_FORMAT_ARGB32, $width, $height, $stride);
$data[0] = "\xFF";
$data[1] = "\xFF";
$data[2] = "\xFF";
$data[3] = "\xFF";

cairo_set_source_surface ($cr, $image, 0, 0);
cairo_paint ($cr);

$status = cairo_surface_write_to_png($surface, "/home/dev/Projects/gtkphp/hello.png");
*/



/*
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
*/



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
$m = new cairo_matrix_t;
cairo_matrix_init_identity($m);

$matrix = new cairo_matrix_t;
cairo_matrix_init_identity($matrix);
//cairo_matrix_init($matrix, "3.14kg", 0.0, 0.0, 0.0, 0.0, 0.0);
$matrix->xx = 2.5;

$rest = new cairo_matrix_t;
cairo_matrix_multiply($rest, $m, $matrix);

var_dump($rest);
*/

