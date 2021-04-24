<?php


if (!extension_loaded("gtk")) die("Gtk+ not loaded");

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);



/*
require_once("Window.php");
//include "Gtkmm.php";


//use Gtk\Orientation{const HORIZONTAL};
use Gtk\{function Init, function Main, const ORIENTATION_HORIZONTAL};
use Gtk\Window;
use Gtk\Box;
use Gtk\Button;


class MyWin extends Window {
    #[Signal('accept', run: 'LAST', slot:function(int, string):bool{})]
    const SIGNAL_ACCEPT=0;
    function __construct() {
        parent::__construct();
        $box = new Box(ORIENTATION_HORIZONTAL, 0);

        $btnAccept = new Button("Valide");
        $btnCancel = new Button("Cancel");

        $box->add($btnAccept);
        $box->add($btnCancel);

        $this->add($box);

        $this->showAll();
    }

    #[Override('GtkWidget::draw')]
    function draw() {
    }

    #[Action('do')]
    function close() {
    }
}

Init($argc, $argv);
$win = new MyWin();
//$win->connect('accept', function($win){echo "Thank you\n";});
//$win->emit('accept');
Main();


*//*


Init($argc, $argv);

$window = new Window();

//G\Signal\Connect($window, "destroy", "on_quit", Null);
//g_signal_connect($window, "destroy", "on_quit", Null);

$box = new Box(ORIENTATION_HORIZONTAL, 0);

$button_a = new Button("Valide");
$button_b = new Button("Cancel");

$box->add($button_a);
$box->add($button_b);


$window->add($box);

$window->showAll();

Main();
*/


/**
 * Test de surcharge
 */
class Btn extends GtkButton {

    /**
     * GtkWidget::getPreferredWidth
     *
     * Because we whant to map name function
     * as we do with connect
     * and keep safe hineritance
     *
     * @override GtkWidget::get_preferred_width
     */
    public function getPreferredWidth(&$minimum_width, &$natural_width):void {
        gtk_widget_get_preferred_width($this, $minimum_width, $natural_width);
        //$minimum_width +=30;
        $natural_width +=50;
    }
    /**
     * Override GtkWidgetClass::draw
     * GtkWidget::get_preferred_width
     * or
     * GtkWidgetClass.get_preferred_width
     *
     * @override GtkWidget::draw
     */
    public function draw($cairo):void {
    }
}

class Div extends GtkBox {

    /*
     * Private Documentation ?
     */
    /** @GtkWidget override('get_preferred_width') */
    /** @override */
    /** @override GtkWidget */
    /** @override GtkWidget::get_preferred_width */
    #[Override('GtkWidget::get_preferred_width')]
    #[Override('get_preferred_width', class: 'GtkWidget')]
    function hello():void {
        echo 'World';
    }
    /** @override GtkWidget(get_preferred_width) */
    /** @signal Div(on-my) */
    function on_my():void {
        echo 'Signal on-my has been emited';
    }
    /** @slot GtkWidget(on-draw) */
    function my_on_draw():void {
        echo 'Signal on-my has been emited';
    }

    /** @gobject connect('on-draw', SIGNAL_AFTER) */
    /** @connect gtkwidget('on-draw', SIGNAL_AFTER) */
    /** @signal object('on-draw', "user_data", SIGNAL_AFTER) */
    /** @slot object('on-draw', "user_data", SIGNAL_AFTER) */
    #[Connect('on-draw', SIGNAL_AFTER)]
    function __on_draw():void {
        echo 'World';
    }

    protected $btn_a;
    protected $btn_b;
    function __construct() {
        parent::__construct();
        $this->btn_a = new Btn();
        $this->btn_b = new GtkButton();
    }
    public function get_preferred_width(&$minimum_width, &$natural_width):void {
        gtk_widget_get_preferred_width($this->btn_a, $minimum, $natural);
        $minimum_width = $minimum;
        $natural_width = $natural;

        gtk_widget_get_preferred_width($this->btn_a, $minimum, $natural);
        $minimum_width += $minimum;
        $natural_width += $natural;
    }
}
//gtk_widget_get_preferred_width($div, $minimum_width, $natural_width);
/*
    \gtk_widget_get_preferred_width(div)
        - call_user(Div::get_preferred_width)// override found
            \gtk_widget_get_preferred_width(btnA)  ------------------------ * recursive[] = #1
                - call_user(Btn::get_preferred_width)// override found
                    \gtk_widget_get_preferred_width(btnA)//??? ------------ ? if isset(#1)
                        - GtkWidget::get_preferred_width()// override found but recursive
            \gtk_widget_get_preferred_width(btnA)
                - GtkWidget::get_preferred_width()// no override
*/


function on_add(GtkContainer $container, GtkWidget $widget, $user_data) {
    echo "on_add(".$widget->label.")\n";

    $children = gtk_container_get_children($container);

    g_list_dump($children);
    g_list_free($children);
    var_dump($children);
}

function on_quit(GtkWidget $object, $user_data) {
    gtk_main_quit();
}

function on_clicked(GtkWidget $button, $user_data) {
    //$button->getPreferredWidth($minimum_width, $natural_width);
    gtk_widget_get_preferred_width($button, $minimum_width, $natural_width);
    echo $minimum_width, ', ', $natural_width, PHP_EOL;
}


gtk_init($argc, $argv);

$window = gtk_window_new();
g_signal_connect($window, "destroy", "on_quit", Null);

$box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
//g_signal_connect($box, "add", "on_add", new StdClass());

$btn = new Btn();
//g_signal_connect($btn, "clicked", "on_clicked", Null);
//$btn->getPreferredWidth($minimum_width, $natural_width);// dot not make override
//gtk_widget_get_preferred_width($btn, $minimum_width, $natural_width);
//echo $minimum_width, ', ', $natural_width, PHP_EOL;


$button_a = gtk_button_new_with_label("Valide");
$button_b = gtk_button_new_with_label("Cancel");
$button_c = gtk_button_new_with_label("Pause");
$button_d = gtk_button_new_with_label("Stop");
///g_signal_connect($button_d, "clicked", "on_quit", Null);

gtk_container_add($box, $btn);
gtk_container_add($box, $button_a);
gtk_container_add($box, $button_b);
gtk_container_add($box, $button_c);
gtk_container_add($box, $button_d);

gtk_container_add($window, $box);

gtk_widget_show_all($box);
gtk_widget_show($window);


function on_destroy(&$data) {
//    var_dump($data);
}
$children = gtk_container_get_children($box);
//$list = $children;
//g_list_dump($children);
//g_list_free($children);
//g_list_free_full($children, "on_destroy");
//var_dump($list);


//TODO: $filename = "https://image.freepik.com/icones-gratuites/symbole-php_318-1694.jpg";
//$filename = "/home/dev/Images/logo-6.png";
//$pixbuf = gdk_pixbuf_new_from_file($filename, $error);
//if($pixbuf) {
//    gtk_window_set_icon($window, $pixbuf);
//} else var_dump($error);
//$list = gtk_window_get_icon_list($window);
//var_dump($list);
//g_list_free($list);

/*
$icon_32 = gdk_pixbuf_new_from_file("/home/dev/Images/logo-6.png", $error);
$icon_16 = gdk_pixbuf_new_from_file("/home/dev/Images/php-icon.png", $error);

$list = null;
$list = g_list_append($list, $icon_16);
$list = g_list_append($list, $icon_32);

gtk_window_set_icon_list($window, $list);

g_list_free_full($list, "g_object_unref");
*/


$list = null;
$list = g_list_append($list, gdk_pixbuf_new_from_file("/home/dev/Images/logo-6.png", $error));
$list = g_list_append($list, gdk_pixbuf_new_from_file("/home/dev/Images/php-icon.png", $error));
g_list_dump($list);

gtk_window_set_icon_list($window, $list);

g_list_free_full($list, "g_object_unref");

$list = gtk_window_get_icon_list($window);
g_list_dump($list);
g_list_free($list);


gtk_main();
