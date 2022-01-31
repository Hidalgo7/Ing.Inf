<?php

    include_once "../clases/conexion.php";
    $id = 19;
    $query = 'CALL `getLibrosComprados`('.$id.');';
    $conexion = new conexion();
    $datos = $conexion->query($query);

    //Para otro formato
    $datos->fetch();
    $datos->fetchAll();
    json_encode($datos->fetchAll());



function getHash($userPath){
    $file = simplexml_load_file($userPath);
    return $file->contrasena;
}

function getIdUsuario($userPath){
    $file = simplexml_load_file($userPath);
    return (string)$file["id"];
}


?>