--TEST--
05-0-0 : Check for cairo_rectangle_int
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


function my_acquire(cairo_pattern_t $pattern,
           $callback_data,
           cairo_surface_t $target,
           cairo_rectangle_int_t $extents): cairo_surface_t
{
    echo "my_acquire called\n";
    return cairo_image_surface_create_from_png ($callback_data);
}

function my_release(cairo_pattern_t $pattern,
           $callback_data,
           cairo_surface_t $surface)
{
    echo "my_release called\n";
}

function my_snapshot(cairo_pattern_t $pattern, $callback_data):int {
    echo "my_snapshot called\n";
    return CAIRO_STATUS_SUCCESS;
}

function my_copy(cairo_pattern_t $pattern, $callback_data, cairo_pattern_t $other):int {
    echo "my_copy called\n";
    return CAIRO_STATUS_SUCCESS;
}

function my_finish(cairo_pattern_t $pattern, $callback_data) {
    echo "my_finish called\n";
}

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

$user_data = "/home/dev/Projects/gtkphp/php-src/ext/gtk/tests/php_cairo/sqaure.png";
$user_data = "/home/dev/Images/checkerboard.png";
$content = CAIRO_CONTENT_COLOR_ALPHA;
$width = 60;
$height = 60;
$pattern = cairo_pattern_create_raster_source($user_data, $content, $width, $height);

cairo_raster_source_pattern_set_acquire($pattern, "my_acquire", "my_release");
cairo_raster_source_pattern_get_acquire($pattern, $acquire, $release);
var_dump($acquire);
var_dump($release);

cairo_raster_source_pattern_set_callback_data($pattern, "/home/dev/Images/checkerboard-2.png");
$data = cairo_raster_source_pattern_get_callback_data($pattern);
var_dump($data);

cairo_raster_source_pattern_set_snapshot($pattern, "my_snapshot");
$snapshot = cairo_raster_source_pattern_get_snapshot($pattern);
var_dump($snapshot);

cairo_raster_source_pattern_set_copy($pattern, "my_copy");
$copy = cairo_raster_source_pattern_get_copy($pattern);
var_dump($copy);


cairo_raster_source_pattern_set_finish($pattern, "my_finish");
$finish = cairo_raster_source_pattern_get_finish($pattern);
var_dump($finish);


cairo_rectangle($cr, 0.0, 0.0, 125.0, 40.0);
cairo_set_source($cr, $pattern);
cairo_pattern_set_extend ($pattern, CAIRO_EXTEND_REPEAT);
cairo_fill($cr);


//cairo_surface_write_to_png($surface, "/home/dev/Projects/gtkphp/hello.png");
$status = cairo_status($cr);
var_dump($status==CAIRO_STATUS_SUCCESS);



?>
--EXPECT--
string(10) "my_acquire"
string(10) "my_release"
string(35) "/home/dev/Images/checkerboard-2.png"
string(11) "my_snapshot"
string(7) "my_copy"
string(9) "my_finish"
my_acquire called
my_release called
bool(true)
