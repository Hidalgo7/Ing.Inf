<?php
    $userPath = "../data/users/".$_POST["usuario"].".xml";
    if(file_exists($userPath)){
        if(password_verify($_POST["contrasena"],getHash($userPath))){
            session_start();
            $_SESSION["idUsuario"] = getIdUsuario($userPath);
            $_SESSION["usuario"] = $_POST["usuario"];
            $_SESSION["carrito"] = array();
            echo "OK";
        }else{
            echo "Usuario o Contraseña Incorrectos";
        }
    }else{
        echo "Usuario o Contraseña Incorrectos";
    }



function getHash($userPath){
    $file = simplexml_load_file($userPath);
    return $file->contrasena;
}

function getIdUsuario($userPath){
    $file = simplexml_load_file($userPath);
    return (string)$file["id"];
}

?>