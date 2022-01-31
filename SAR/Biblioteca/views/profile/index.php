<?php


    if(!isset($_SESSION["usuario"])){
        session_start();
    }
    //$_SESSION['username'] = 'hidalgo';
    if (isset($_SESSION['idUsuario'])){
        include_once "../../clases/conexion.php";
        $userPath = '../../data/users/'.$_SESSION['usuario'].'.xml';
        $user = simplexml_load_file($userPath);
        $query = 'CALL `getLibrosComprados`('.$_SESSION['idUsuario'].');';
        $conexion = new conexion();
        $libros = $conexion->query($query);
        $libros = $libros->fetchAll();

        include_once('profile.html.php');

    }
    else{
        $message = "Inicia sesion para ver tu perfil.";
        echo "<script type='text/javascript'>alert('$message');
        window.location.href='../home';</script>";
    }

    
?>