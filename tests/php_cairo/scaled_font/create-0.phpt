--TEST--
05-0-0 : Check for cairo_image_surface_get_width
--SKIPIF--
<?php if (!extension_loaded("gtk")) print "skip";
print "skip";
?>
--FILE--
<?php

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);
/*


$font_face = font_face;
$scaled_font = cairo_scaled_font_create (cairo_font_face_t *font_face,
                          const cairo_matrix_t *font_matrix,
                          const cairo_matrix_t *ctm,
                          const cairo_font_options_t *options);
*/

?>
--EXPECT--
