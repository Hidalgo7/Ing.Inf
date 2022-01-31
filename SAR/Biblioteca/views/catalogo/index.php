<?php
    include_once "../../clases/libros.php";

    $libro = new libroClass();

    $listaLibros = $libro->getLibroList();

    unset($libro);

    include_once "catalogo.html.php";
?>