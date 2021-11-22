--TEST--
05-0-0 : Check for cairo_image_surface_create
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php

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


$surface = cairo_image_surface_create ($format, 250, 80);
$cr = cairo_create ($surface);

$image = cairo_image_surface_create_for_data ($data, CAIRO_FORMAT_ARGB32, $width, $height, $stride);

cairo_set_source_surface ($cr, $image, 0, 0);
cairo_paint ($cr);

$expect = __DIR__."/../checkerboard-expect.png";
$output = __DIR__."/../checkerboard-output.png";
$status = cairo_surface_write_to_png($surface, $output);
var_dump($status==CAIRO_STATUS_SUCCESS);
$diff = `diff $expect $output`;
var_dump($diff);

/*
echo strlen(cairo_image_surface_get_data ($image)).PHP_EOL;
echo cairo_image_surface_get_height ($image).PHP_EOL;
echo cairo_image_surface_get_width ($image).PHP_EOL;
echo cairo_image_surface_get_stride ($image).PHP_EOL;
*/

?>
--EXPECT--
bool(true)
NULL
