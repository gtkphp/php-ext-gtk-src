<?php

class MyWidget : public Gtk\Widget
{
    /**
     * @var Gtk\StyleProperty<int> $_scaleProp
     */
    protected $_scaleProp;
    /**
     * @var Gdk\Window $_refGdkWindow
     */
    protected $_refGdkWindow;
    /**
     * @var Gtk\CssProvider $_refCssProvider
     */
    protected $_refCssProvider;
    /**
     * @var int $_scale
     */
    protected $_scale;

    public function __construct() {
        //The GType name will actually be php__my_namespace_mywidget
        //The GType name will actually be gtkmm__CustomObject_mywidget
        //Glib::ObjectBase("mywidget"),
        parent::__construct();
        //Install a style property so that an aspect of this widget may be themed
        //via a CSS style sheet file:
        $this->_scaleProp = new Gtk\StyleProperty($this, "example_scale", 500);
        $this->__scale = 1000;

        $this->setHasWindow(true);

        //This shows the GType name, which must be used in the CSS file.
        echo "GType name: ", G\Object::TypeName($this), PHP_EOL;

        //This shows that the GType still derives from GtkWidget:
        //std::cout << "Gtype is a GtkWidget?:" << GTK_IS_WIDGET(gobj()) << std::endl;
        echo "Gtype is a GtkWidget?:", Gtk\IsWidget($this), PHP_EOL;

        // Set the widget name to use in the CSS file.
        $this->setName("my-widget");

        // If you make a custom widget in C code, based on gtk+'s GtkWidget, there is
        // an alternative to gtk_widget_set_name(): Set a CSS name for your custom
        // class (instead of the widget instance) with gtk_widget_class_set_css_name()
        // (new in gtk+ 3.19.1). That's not possible for custom widgets defined in gtkmm.
        // gtk_widget_class_set_css_name() must be called in the class init function,
        // which can't be customized, when the widget is based on gtkmm's Gtk::Widget.
        //
        // Another alternative: The custom widget inherits the CSS name "widget" from
        // GtkWidget. That name can be used in the CSS file. This is not a very good
        // alternative. GtkWidget's CSS name is not documented. It can probably be
        // changed or removed in the future.

        $this->_refCssProvider = new Gtk\CssProvider();
        $refStyleContext = $this->getStyleContext();
        $refStyleContext->addProvider($this->_refCssProvider,
            GTK\STYLE_PROVIDER_PRIORITY_APPLICATION);
        $this->_refCssProvider->connect('parsing-error',//----------------------------
            [$this, 'on_parsing_error']);

        try {
            $this->_refCssProvider->loadFromPath("custom_gtk.css");
        } catch(Gtk\CssProviderError $ex) {
            echo "CssProviderError, Gtk\\CssProvider::loadFromPath() failed: "
                    , $ex->what(), PHP_EOL;
        } catch(Glib\Error $ex) {
            echo "Error, Gtk\\CssProvider::loadFromPath() failed: "
                    , $ex->what(), PHP_EOL;
        }

    }

    public function __destruct() {
        parent::__destruct();
    }

    /**
     * @override GtkWidget::get_request_mode
     */
    protected function getRequestMode():Gtk\SizeRequestMode {
        //Accept the default value supplied by the base class.
        return parent::getRequestMode();
    }

    /**
     * @override GtkWidget::get_preferred_width
     */
    protected function getPreferredWidth(int &$minimum_width,int &$natural_width) {
        $minimum_width = 60;
        $natural_width = 100;
    }

    /**
     * @override GtkWidget::get_preferred_height_for_width
     */
    protected function getPreferredHeightForWidth(int $width, int &$minimum_height, int &$natural_height) {
        $minimum_height = 50;
        $natural_height = 70;
    }

    /**
     * @override GtkWidget::get_preferred_height
     */
    protected function getPreferredHeight(int &$minimum_height, int &$natural_height) {
        $minimum_height = 50;
        $natural_height = 70;
    }

    /**
     * @override GtkWidget::get_preferred_width_for_height
     */
    protected function getPreferredWidthForHeight(int $height, int &$minimum_width, int &$natural_width) {
        $minimum_width = 60;
        $natural_width = 100;
    }

    /**
     * @override GtkWidget::size_allocate
     */
    protected function sizeAllocate(Gtk\Allocation &$allocation) {
        //Do something with the space that we have actually been given:
        //(We will not be given heights or widths less than we have requested, though
        //we might get more)

        //Use the offered allocation for this container:
        $this->setAllocation($allocation);

        if($this->_refGdkWindow) {
            $this->_refGdkWindow->moveResize( allocation['x'], $allocation->getY(),
            $allocation->getWidth(), $allocation['height'] );
        }
    }

    /**
     * @override GtkWidget::map
     */
    protected function map() {
        //Call base class:
        gtk_widget_on_map($this);
    }

    /**
     * @override GtkWidget::unmap
     */
    protected function unmap() {
        //Call base class:
        parent::unmap();
    }

    /**
     * @override GtkWidget::realize
     */
    protected function realize() {
        $this->setRealized();

        //Get the themed style from the CSS file:
        $this->_scale = $this->_scaleProp->getValue();
        echo "m_scale (example_scale from the theme/css-file) is: "
            , $this->_scale, PHP_EOL;

        if(!m_refGdkWindow) {
            //Create the GdkWindow:

            $attributes = new Gdk\WindowAttr;
            $allocation = $this->getAllocation();// of Gtk\Allocation

            //Set initial position and size of the Gdk::Window:
            $attributes->x = $allocation->getX();
            $attributes->y = $allocation->getY();
            $attributes->width = $allocation->getWidth();
            $attributes->height = $allocation->getHeight();

            $attributes->eventMask = $this->getEvents() | Gdk\EXPOSURE_MASK;
            $attributes->windowType = Gdk\WINDOW_CHILD;
            $attributes->wclass = Gdk\INPUT_OUTPUT;

            $this->_refGdkWindow = Gdk\Window::create($this->getParentWindow(), &attributes,
            Gdk\WA_X | Gdk\WA_Y);
            $this->setWindow($this->_refGdkWindow);

            //make the widget receive expose events
            $this->_refGdkWindow->setUserData($this);
        }
    }

    /**
     * @override GtkWidget::unrealize
     */
    protected function unrealize() {
        $this->_refGdkWindow->reset();

        //Call base class:
        Gtk\Widget::unrealize();
    }

    /**
     * @override GtkWidget::draw
     */
    protected function draw(Cairo\Context $cr) {
        $allocation = $this->getAllocation();// of Gtk\Allocation
        $scaleX = (double)$allocation->getWidth() / $this->_scale;
        $scaleY = (double)$allocation->getHeight() / $this->_scale;
        $refStyleContext = $this->getStyleContext();

        // paint the background
        $refStyleContext->renderBackground($cr,
            $allocation->getX(), $allocation->getY(),
            $allocation->getWidth(), $allocation->getHeight());

        // draw the foreground
        $state = $refStyleContext->getState();
        $cr->setSourceRgba($cr, $refStyleContext->getColor($state));
        $cr->moveTo(155.*$scale_x, 165.*$scale_y);
        $cr->lineTo(155.*$scale_x, 838.*$scale_y);
        $cr->lineTo(265.*$scale_x, 900.*$scale_y);
        $cr->lineTo(849.*$scale_x, 564.*$scale_y);
        $cr->lineTo(849.*$scale_x, 438.*$scale_y);
        $cr->lineTo(265.*$scale_x, 100.*$scale_y);
        $cr->lineTo(155.*$scale_x, 165.*$scale_y);
        $cr->moveTo(265.*$scale_x, 100.*$scale_y);
        $cr->lineTo(265.*$scale_x, 652.*$scale_y);
        $cr->lineTo(526.*$scale_x, 502.*$scale_y);
        $cr->moveTo(369.*$scale_x, 411.*$scale_y);
        $cr->lineTo(633.*$scale_x, 564.*$scale_y);
        $cr->moveTo(369.*$scale_x, 286.*$scale_y);
        $cr->lineTo(369.*$scale_x, 592.*$scale_y);
        $cr->moveTo(369.*$scale_x, 286.*$scale_y);
        $cr->lineTo(849.*$scale_x, 564.*$scale_y);
        $cr->moveTo(633.*$scale_x, 564.*$scale_y);
        $cr->lineTo(155.*$scale_x, 838.*$scale_y);
        $cr->stroke();

        return true;
    }

    /**
     *
     */
    protected function onParsingError(Gtk\CssSection $section, Glib\Error &$error) {
        echo "on_parsing_error(): ", error->what(), PHP_EOL;
        if ($section) {
            $file = $section->getFile();
            if ($file) {
                echo "  URI = ", file->getUri(), PHP_EOL;
            }

            echo "  start_line = " << $section->getStartLine()+1
                    , ", end_line = ", $section->getEndLine()+1, PHP_EOL;
            echo "  start_position = ", $section->getStartPosition()
                    , ", end_position = ", $section->getEndPosition(), PHP_EOL;
        }
    }

};
