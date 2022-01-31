<?php
    session_start();
    include_once "../clases/conexion.php";

    if(isset($_SESSION["usuario"])){
        $conexion = new conexion();
        $query = "SELECT * FROM catalogo WHERE id IN (".implode(",",$_SESSION["carrito"]).");";
        $datos = $conexion->query($query);
        echo json_encode($datos->fetchAll());
    }

?>