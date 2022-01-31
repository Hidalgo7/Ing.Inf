<?php
    session_start();
    include_once "../clases/conexion.php";

    if(isset($_SESSION["usuario"])){
        $conexion = new conexion();

        foreach($_SESSION["carrito"] as $idLibro) {
            $query = 'CALL `insertCompra`('.$_SESSION["idUsuario"].','.$idLibro.');';
            $datos = $conexion->query($query);
        }
        $_SESSION["carrito"] = array();
        echo "OK";
    } else{
        echo "No se puede añadir a cesta sin iniciar sesion!";
}



?>