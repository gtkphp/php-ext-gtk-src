<?php

declare(strict_types=0);
//declare(fatal_warnings=1);


if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', '1');
ini_set('display_startup_errors', '1');
error_reporting(E_ALL);


/*
$rect = new cairo_rectangle_t();
$rect->x += 1.0;
$rect->y = 3;
var_dump($rect);
*/

/*
$path = new cairo_path_t();
$path->data[] = new cairo_path_data_t(CAIRO_PATH_LINE_TO);
$path->data[] = new cairo_path_data_t(60.0, 20.0);
var_dump($path);
*/

/*
$path = new cairo_path_t();
$ref = &$path->data;
$ref[] = new cairo_path_data_t(CAIRO_PATH_MOVE_TO);
$ref[] = new cairo_path_data_t(0.0, 0.0);

$path_data = array();
$path_data[] = new cairo_path_data_t(CAIRO_PATH_MOVE_TO);
$path_data[] = new cairo_path_data_t(0.0, 0.0);
$path->data = $path_data;
*/

/*
$foo = new cairo_path_data_t(CAIRO_PATH_LINE_TO);
var_dump($foo);
$header = $foo->header;
$point = new StdClass();
$point->x = 0.0;
$point->y = 0.0;
$foo->point = $point;
var_dump($foo);
var_dump($header);
*/

/*

$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);
cairo_move_to($cr, 1.0, 0.0);
cairo_line_to($cr, 21.0, 20.0);


$path = cairo_copy_path($cr);// <----------- convert cairo_path_to ZVAL_ARRAY


var_dump($path);

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

//$point = &$path->data[0]->point; varnish error return null
//var_dump($path);



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

//var_dump($path);
//var_dump($path->num_data);

cairo_set_source_rgb ($cr, 0.0, 1.0, 0.0);
cairo_append_path($cr, $path);

cairo_stroke ($cr);

$status = cairo_surface_write_to_png($surface, "/home/dev/Projects/gtkphp/hello.png");
*/


//$path->data[1]->point->x += 10.0;

//cairo_append_path($cr, $path);// <----------- convert $path->data array as cairo_path_data_t structure helped by cairo_t

//cairo_path_destroy($cr);

//var_dump($path);

/*
$rect = new cairo_rectangle_t();//0.0, 0.0, 0.0, 0.0
$rect->x = 10.0;
$rect->y = 20.0;
$rect->width = 110.0;
$rect->height = 90.0;
$rect->height += 10.0;// get_property_ptr_ptr not implemented => Error Undefined property: cairo_rectangle_t::$height
var_dump($rect);
*/

/*
$surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 250, 80);
$cr = cairo_create ($surface);

//cairo_move_to ($cr, 64.0, 25.6);
cairo_rectangle ($cr, 0.0, 0.0, 21.0, 29.7);

$path = cairo_copy_path ($cr);

//cairo_append_path ($cr, $path);


//var_dump($path);
//var_dump($path->num_data);
//var_dump($path->data[0]);

$path_data = $path->data;
for ($i=0; $i < $path->num_data; $i += $path_data[$i]->header->length) {
    switch ($path_data[$i]->header->type) {
    case CAIRO_PATH_MOVE_TO:
        echo "CAIRO_PATH_MOVE_TO(".$path_data[$i+1]->point->x.", ".$path_data[$i+1]->point->y.")\n";
        break;
    case CAIRO_PATH_LINE_TO:
        echo "CAIRO_PATH_LINE_TO(".$path_data[$i+1]->point->x.", ".$path_data[$i+1]->point->y.")\n";
        $point = $path_data[$i+1]->point;
        $point->x = $point->x + 10.0;
        break;
    }
}
var_dump($path);
*/

/*
for ($i=0; $i < $path->num_data; $i += $path->data[$i]->header->length) {
    switch ($path->data[$i]->header->type) {
    case CAIRO_PATH_MOVE_TO:
        echo "CAIRO_PATH_MOVE_TO(".$path->data[$i+1]->point->x.", ".$path->data[$i+1]->point->y.")\n";
        break;
    case CAIRO_PATH_LINE_TO:
        echo "CAIRO_PATH_LINE_TO(".$path->data[$i+1]->point->x.", ".$path->data[$i+1]->point->y.")\n";
        //$path->data[$i+1]->point->x += 10;
        break;
    }
}
*/





/*
$ret = new cairo_rectangle_t();

$matrix = new cairo_matrix_t();
$a = new cairo_matrix_t();
$b = new cairo_matrix_t();

cairo_matrix_init_identity($a);
cairo_matrix_scale($a, 2.0, 2.0);
cairo_matrix_init_identity($b);
cairo_matrix_multiply($matrix, $a, $b);

var_dump($matrix);
$matrix->xx += 0.5;
print_r($matrix);
*/


/*
$rect = new cairo_rectangle_t();//0.0, 0.0, 0.0, 0.0
$rect->x = 10.0;
$rect->y = 20.0;
$rect->width = 110.0;
$rect->height = 90.0;
$rect->foo = "hello";
var_dump($rect->foo);
var_dump($rect);
//print_r((array)$rect);
//print_r($rect);

//$r = GdkRectangle::__set_state((array)$rect);
//var_dump($b);
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




--------------------------------------------------------------
- Reflection for override GtkWidget::get_prefered_width
--------------------------------------------------------------

GtkWidgetClass *klass;
origin = klass->get_prefered_width;
klass->get_prefered_width = function() {

#if 0
    zend_object *zobj = Z_OBJ_P(getThis());
    zval obj;
    zend_reflection_class_factory(zobj->ce, &obj);
    zend_class_entry *ref = obj.value.obj->ce;
    g_print("reflection: %s\n", ref->name->val);


    zend_string *lc_method_name = zend_string_init("getDocComment", strlen("getDocComment"), 0);
    zend_function *fbc;
    fbc = zend_hash_find_ptr(&ref->function_table, lc_method_name);

    zval retval_ptr;
    zval function_name; ZVAL_STR(&function_name, lc_method_name);
    uint32_t param_count = 0;
    zval params[0];
    int no_separation = 0;
    int ret = _call_user_function_ex(&obj, &function_name, &retval_ptr, param_count, params, no_separation);
    g_print("%d == %d\n", IS_STRING, Z_TYPE(retval_ptr));
    g_print("%s\n", retval_ptr.value.str->val);


    zend_function *fdecl;
    ZEND_HASH_FOREACH_PTR(&zobj->ce->function_table, fdecl) {
        g_print("  + %s\n", fdecl->common.function_name->val);
        // $reflector->getMethod('get_preferred_width')->getDocComment();
    } ZEND_HASH_FOREACH_END();
#endif

