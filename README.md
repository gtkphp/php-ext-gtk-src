# PHP bindings for GTK+
The GTK+PHP project provides php5> bindings for GTK+4,3,2 in a one API.
It is intended for creating Hybrid GUI applications.

Partial binding support for the following libraries is currently implemented:

- GTK
- GLib ![GLib](https://github.com/gtkphp/php-ext-gtk-src/actions/workflows/ci.yml/badge.svg?branch=shield)
- Pango
- Cairo

Care has been taken for memory management to work seamlessly with php's
garbage collector without the need to use or understand GObject's
floating references.

For better understanding see
[package reference documation](https://gtk.php.net/gtk3?tab=doc)


## Sample Use

The following example can be found in [Examples](https://github.com/gtkphp/hello-world-examples/).

```
<?php
class Window extends Gtk\Window {
    public function __construct() {
        parent::__construct();
        G\Signal\Connect($this, "destroy", "Gtk\MainQuit", null);
    }
}

Gtk\Init($argc, $argv);
$window = new Window;
$window->showAll();
Gtk\Main();
```

## Documentation


## Requirements


## Installation

## Testing


## TODO

- Add bindings for all of GTK functions
- Add tests for each implemented binding

- cairo
- [x] cairo_antialias_t
- [x] cairo_fill_rule_t
- [x] cairo_line_cap_t
- [x] cairo_line_join_t
- [x] cairo_operator_t
- [x] cairo_path_data_type_t
- [x] cairo_extend_t
- [x] cairo_filter_t
- [x] cairo_pattern_type_t
- [x] cairo_region_overlap_t
- [x] cairo_font_slant_t
- [x] cairo_font_weight_t
- [x] cairo_text_cluster_flags_t
- [x] cairo_font_type_t
- [x] cairo_subpixel_order_t
- [x] cairo_hint_style_t
- [x] cairo_hint_metrics_t
- [x] cairo_device_type_t
- [x] cairo_content_t
- [x] cairo_surface_type_t
- [x] cairo_format_t (+ Image Surfaces functions)
- [x] cairo_status_t
- [ ] -----------------------------
- [ ] cairo_t
- [X] cairo_rectangle_t
- [X] cairo_rectangle_list_t
- [X] cairo_path_t
- [ ] cairo_pattern_t
- [ ] cairo_region_t
- [ ] cairo_glyph_t
- [ ] cairo_text_cluster_t
- [ ] cairo_font_face_t
- [ ] cairo_scaled_font_t
- [ ] cairo_font_extents_t
- [ ] cairo_text_extents_t
- [ ] cairo_font_options_t
- [ ] cairo_device_t
- [ ] cairo_surface_t ( Work in progress)
- [X] cairo_matrix_t
- [ ] -----------------------------
- [X] cairo_path_data_t
- [ ] -----------------------------
- [ ] cairo_transforms
- [ ] cairo_raster_source
- [ ] cairo_tag
- [ ] cairo_ft
- [ ] cairo_win32_fonts
- [ ] cairo_user_fonts
- [ ] cairo_pdf
- [ ] cairo_png
- [ ] cairo_ps
- [ ] cairo_recording
- [ ] cairo_win32
- [ ] cairo_svg
- [ ] cairo_quartz
- [ ] cairo_xcb
- [ ] cairo_xlib
- [ ] cairo_xlib_xrender
- [ ] cairo_script
- [ ] cairo_types

## License

GPL-3.0
