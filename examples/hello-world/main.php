<?php

function print_hello (GtkWidget $widget, $data):void {
  echo "Hello World\n";
}

function activate (GtkApplication $app, $user_data):void {

  $window = gtk_application_window_new ($app);
  gtk_window_set_title ($window, "Window");
  gtk_window_set_default_size ($window, 200, 200);

  $button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add ($window, $button_box);

  $button = gtk_button_new_with_label ("Hello World");
  g_signal_connect ($button, "clicked", 'print_hello', null);
  g_signal_connect_swapped ($button, "clicked", 'gtk_widget_destroy', $window);
  gtk_container_add ($button_box, $button);

  gtk_widget_show_all ($window);
}


$app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
g_signal_connect ($app, "activate", 'activate', null);
$status = g_application_run ($app, $argc, $argv);
g_object_unref($app);

exit($status);
