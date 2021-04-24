<?php

namespace Cairo;


class Matrix extends \cairo_matrix_t {
    public function __construct() {
        parent::__construct();
    }
    public function init(float $xx, float $xy, float $yx, float $yy, float $x0, float $y0):Matrix {
        \cairo_matrix_init($this, $xx, $xy, $yx, $yy, $x0, $y0);
        return $this;
    }
    public function initIdentity():Matrix {
        \cairo_matrix_init_identity($this);
        return $this;
    }

}


// class Matrix extends \CairoMatrix {}
