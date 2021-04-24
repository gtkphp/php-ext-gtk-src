<?php

include "MyWidget.php"


class ExampleWindow extends Gtk\Window
{
    /**
     * @var Gtk\Box $_vBox
     */
    protected $_vBox;
    /**
     * @var MyWidget $_myWidget;
     */
    protected $_myWidget;
    /**
     * @var Gtk\ButtonBox $_buttonBox;
     */
    protected $_buttonBox;
    /**
     * @var Gtk\Button $_buttonBox;
     */
    protected $_buttonQuit;

    function __construct() {
        parent::__construct();
        $this->_vBox = new Gtk\Box(Gtk\ORIENTATION_VERTICAL);
        $this->_buttonQuit = new Gtk\Button("Quit");

        $this->setTitle("Custom Widget example");
        $this->setBorderWidth(6);
        $this->setDefaultSize(400, 200);

        $this->add($this->_vBox);
        $this->_vBox->packStart($this->_myWidget, Gtk\PACK_EXPAND_WIDGET);
        $this->_myWidget->show();

        $this->_vBox->packStart($this->_buttonBox, Gtk\PACK_SHRINK);

        $this->_buttonBox->packStart($this->_buttonQuit, Gtk\PACK_SHRINK);
        $this->_buttonBox->setBorderWidth(6);
        $this->_buttonBox->setLayout(Gtk\BUTTONBOX_END);
        $this->_buttonQuit->connect('clicked', [$this, 'on_button_quit'], null);

        $this->showAllChildren();
    }

    function on_button_quit($buttonQuit, $user_data):void {
        $this->hide();
    }
};
