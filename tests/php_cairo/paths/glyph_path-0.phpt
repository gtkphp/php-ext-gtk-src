--TEST--
05-0-0 : Check for cairo_path_destroy
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip"; ?>
--FILE--
<?php


$surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 270, 50);
$cr = cairo_create($surface);

cairo_rectangle ($cr, 0.0, 0.0, 270.0, 50.0);
cairo_set_source_rgb ($cr, 1.0, 1.0, 1.0);
cairo_fill ($cr);

$glyphs = array();
for($i=0; $i<26; $i++) {
    $glyph = new cairo_glyph_t;
    $glyph->index = 68+$i;//ord('a')?
    $glyph->x = 10.0*$i;
    $glyph->y = 10.0;
    $glyphs[] = $glyph;
}

cairo_select_font_face ($cr, "Handel Gothic Medium",//Sans
            CAIRO_FONT_SLANT_NORMAL,
            CAIRO_FONT_WEIGHT_NORMAL);
cairo_set_font_size ($cr, 12);

cairo_glyph_path($cr, $glyphs);
cairo_set_source_rgb ($cr, 0.0, 0.0, 0.0);
cairo_fill ($cr);

//$status = cairo_surface_write_to_png($surface, "/home/dev/Projects/gtkphp/hello.png");
$status = cairo_status($cr);

var_dump($status==CAIRO_STATUS_SUCCESS);


?>
--EXPECT--
bool(true)
