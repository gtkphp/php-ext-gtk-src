<?php

declare(strict_types=0);

if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', '1');
ini_set('display_startup_errors', '1');
error_reporting(E_ALL);

confirm_gtk_compiled("");

/*
$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);
cairo_move_to($cr, 1.0, 0.0);
cairo_line_to($cr, 21.0, 20.0);

$path = cairo_copy_path($cr);


$path_data = $path->data;
for ($i=0; $i < $path->num_data; $i += $path_data[$i]->header->length) {
    switch ($path_data[$i]->header->type) {
        case CAIRO_PATH_MOVE_TO:
            echo "CAIRO_PATH_MOVE_TO(";
            echo $path->data[$i+1]->point->x.", ".$path_data[$i+1]->point->y;
            echo ")\n";
            $point = $path->data[$i+1]->point;
            $point->x += 10.0;
            break;
        case CAIRO_PATH_LINE_TO:
            echo "CAIRO_PATH_LINE_TO(";
            echo $path_data[$i+1]->point->x.", ".$path_data[$i+1]->point->y;
            echo ")\n";
            $path_data[$i+1]->point->x += 10.0;
            break;
    }
}


$path->data[] = new cairo_path_data_t(CAIRO_PATH_LINE_TO);
$path->data[] = new cairo_path_data_t(60.0, 20.0);


cairo_set_source_rgb ($cr, 1.0, 0, 0);
cairo_stroke ($cr);


cairo_set_source_rgb ($cr, 0.0, 0, 1.0);
cairo_append_path($cr, $path);
cairo_stroke ($cr);


$path = new cairo_path_t();
$path->data[] = new cairo_path_data_t(CAIRO_PATH_MOVE_TO);
$path->data[] = new cairo_path_data_t(0.0, 0.0);
$path->data[] = new cairo_path_data_t(CAIRO_PATH_CURVE_TO);
$path->data[] = new cairo_path_data_t(20.0, 60.0);
$path->data[] = new cairo_path_data_t(40.0, 60.0);
$path->data[] = new cairo_path_data_t(80.0, 00.0);

cairo_set_source_rgb ($cr, 0.0, 1.0, 0.0);
cairo_append_path($cr, $path);
cairo_stroke ($cr);


$path_data=[];
$path_data[] = new cairo_path_data_t(CAIRO_PATH_MOVE_TO);
$path_data[] = new cairo_path_data_t(0.0, 0.0);
$path_data[] = new cairo_path_data_t(CAIRO_PATH_LINE_TO);
$path_data[] = new cairo_path_data_t(50.0, 25.0);
$path = new cairo_path_t();
$path->data = $path_data;
var_dump($path);

cairo_set_source_rgb ($cr, 0.0, 1.0, 0.0);
cairo_append_path($cr, $path);

cairo_stroke ($cr);

$status = cairo_surface_write_to_png($surface, "/home/dev/Projects/gtkphp/hello.png");
*/
