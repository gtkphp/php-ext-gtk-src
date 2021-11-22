<?php

if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);


define("g_signal_new_id", 1);
define("g_param_spec_new_id", 1);



class GlibObject extends GObject {
    /**
     * @g_param_spec_uint("zoom",
     *                    "Zoom construct prop",
     *                    "Set zoom's name",
     *                    0, 100,
     *                    51,
     *                    G_PARAM_CONSTRUCT | G_PARAM_READWRITE)
     */
    public $zoom=41;

    /**
     * @g_signal_new("changed",
     *               G_TYPE_OBJECT,
     *               G_SIGNAL_RUN_LAST, NULL,
     *               NULL, NULL,
     *               G_TYPE_INT, 1, G_TYPE_INT)
     */
    const CHANGED = g_signal_new_id;

    /*function __notify(string $name, mixed $value){}*/
}


function this_is_my_callback(GObject $object, GParamSpec $param, $user_data){
    echo $param->name."\e[0;31m ->my_callback($object->zoom)\e[0m'$user_data'", PHP_EOL;
    //echo "Call\n";
}

function on_changed(GObject $object, $param, $user_data){
    echo "\e[0;31m ->on_changed($param)\e[0m", PHP_EOL;
    return 3;
}

$object = new GlibObject();
//gtk_init($argc, $argv);
//$object = new GtkBox();
//$object = new GtkContainer();
//$object = new GtkBin();


//g_signal_connect($object, "notify::zoom", "this_is_my_callback", "my_data");

/*
g_object_connect($object,
                "signal::notify::zoom", "this_is_my_callback", "my_data",
                "signal::changed", "on_changed", "my_data",
                NULL);

$pspec = g_object_class_find_property(g_type_name_from_instance($object), "zoom");
g_signal_emit_by_name($object, "notify", $pspec, "data");

g_signal_emit_by_name($object, "changed", 10, NULL);
$object->zoom=71; // g_signal_emit_by_name();
*/

/*
$value = new GValue(G_TYPE_UINT);
g_value_set_uint($value, 47);
g_object_set_property($object, "zoom", $value);
*/

/*
GType $type = g_type_from_name(GlibObject::class);
$klass=$type
GParamSpec *pspec = g_object_class_find_property($klass, "zoom");
int $signal_id = GlibObject::CHANGED; //g_signal_lookup("notify", $type);
g_signal_emit($object, $signal_id, g_quark_from_string("zoom"), $pspec, $ret);
*/

var_dump($object);

//$object["zoom"]=71;
//$signal_id = $object["notify::zoom"];
//$signal_id = $object["signal::zoomed"];
//$spec_id = $object["style::max_zoom"];
//$spec_id = $object["data::zoomed"];
