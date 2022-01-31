<?php
    session_start();
    include_once "../clases/conexion.php";

    if(isset($_SESSION["usuario"])){
        $conexion = new conexion();
        $query = "CALL `getBookInfo`('".$_POST["id"]."')";
        $datos = $conexion->query($query);
        array_push($_SESSION["carrito"],$_POST["id"]);
    } else{
        echo "No se puede añadir a cesta sin iniciar sesion!";
    }

?>