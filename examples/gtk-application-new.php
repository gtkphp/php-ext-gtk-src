<?php

// C-Style( Php4>)

function on_clicked($button, $event, $window) {
    $window->close ();
}

function on_activate($app) {
    // Create a new window
    $window = gtk_application_window_new ($app);

    // Create a new button
    $button = gtk_button_new_with_label("Hello, World!");

    // When the button is clicked, close the window
    g_signal_connect ($button, 'clicked', "on_clicked", $window);

    $window->setChild ($button);
    $window->present ();
}

$app = gtk_application_new ("net.php.GtkApplication");
g_signal_connect($app, 'activate', "on_activate", Null);
$status = $app->run ($argv);

exit($status);

//------------------------------
// Poo-Style( Php5>)
function on_clicked($button, $event, $window) {
    $window->close ();
}

function on_activate($app) {
    // Create a new window
    $window = new Gtk\ApplicationWindow ($app);

    // Create a new button
    $button = new Gtk\Button(label: "Hello, World!");

    // When the button is clicked, close the window
    $button->connect ('clicked', "on_clicked", $window);

    $window->setChild ($button);
    $window->present ();
}

$app = new Gtk\Application ("net.php.GtkApplication");
$app->connect ('activate', "on_activate");
$status = $app->run ($argv);

exit($status);

//------------------------------
// Poo-Style( Php7>)

$app = new Gtk\Application ("net.php.GtkApplication");

$app->connect ('activate', function() use($app) {
    // Create a new window
    $window = new Gtk\ApplicationWindow ($app);

    // Create a new button
    $button = new Gtk\Button(label: "Hello, World!");

    // When the button is clicked, close the window
    $button->connect ('clicked', function() use($window) { $window->close (); });

    $window->setChild ($button);
    $window->present ();
}/*, Null*/);

$status = $app->run ($argv);

exit($status);

//------------------------------
// Gtkmm-Style( Php8)

class MyBtn extends Gtk\Button {
    // When the button is clicked, close the window
    function clicked($window) {
        $window->close ();
    }
}

class MyApp extends Gtk\Application {

    #[Signal('my-action', flag: RUN_FIRST | RUN_LAST, slot: myAction, )]
    const MY_ACTION = function(object $widget, $event, $data):int{};

    #[Slot('/path', name: 'action')]
    function activate($userData) {
        // Create a new window
        $window = new Gtk\ApplicationWindow ($this);

        // Create a new button
        $button = new MyBtn(label: "Hello, World!");

        $window->setChild ($button);
        $window->present ();
    }
}

$app = new MyApp ("net.php.GtkApplication");
$status = $app->run ($argv);
//emit MY_ACTION(value);
