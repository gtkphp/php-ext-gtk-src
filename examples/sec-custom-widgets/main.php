<?php

include "ExampleWindow.php"

$app = Gtk\Application::create($argc, $argv, "net.php.gtk");

$window = new ExampleWindow;

//Shows the window and returns when it is closed.
$status = $app->run($window);

exit($status);
