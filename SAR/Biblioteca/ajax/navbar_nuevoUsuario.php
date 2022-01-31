<?php

$userPath = "../data/users/".$_POST["usuario"].".xml";

$res = datosCorrectos($userPath);
if($res =="OK") {
    crearUsuario();
    session_start();
    $_SESSION["idUsuario"] = getIdUsuario($userPath);
    $_SESSION["usuario"] = $_POST["usuario"];
    $_SESSION["carrito"] = array();
}
echo $res;


function datosCorrectos($userPath){

    // Comprobar longitud
    if(strlen($_POST["usuario"])<5){
        return "Nombre de usuario demasiado corto";
    }
    if(strlen($_POST["nombre"])<2){
        return "Nombre demasiado corto";
    }
    if(strlen($_POST["apellido"])<2){
        return "Nombre de usuario demasiado corto";
    }
    if(strlen($_POST["fechaNacimiento"])<5){
        return "Formato de fecha incorrecto";
    }
    if(strlen($_POST["email"])<7){
        return "Email demasiado corto";
    }
    if(strlen($_POST["contrasena"])<6){
        return "La contraseña debe de contener al menos 6 letras";
    }

    // Comprobar si el usuario ya existe
    if(file_exists($userPath)){
        return "El nombre de usuario ya esta en uso";
    }
    // Comprobar contraseña minimo 1 numero
    if(!preg_match("#[0-9]+#",$_POST["contrasena"])){
        return "La contraseña debe tener al menos 1 digito";
    }

    // Comprobar formato correo
    if (!filter_var($_POST["email"], FILTER_VALIDATE_EMAIL)) {
        return "El formato del email es incorrecto";
    }

    return "OK";
}


function getIdUsuario($userPath){
    $file = simplexml_load_file($userPath);
    return (string)$file["id"];
}

function crearUsuario(){
    $dom = new DOMDocument();

    $dom->encoding = 'utf-8';
    $dom->xmlVersion = '1.0';
    $dom->formatOutput = true;

    $xml_file_name = '../data/users/'.$_POST["usuario"].".xml";

    $root = $dom->createElement('usuario');
    $id = new DOMAttr('id', nuevaId());
    $root->setAttributeNode($id);

    $usuario = $dom->createElement('usuario',$_POST["usuario"]);
    $nombre = $dom->createElement('nombre',$_POST["nombre"]);
    $apellido = $dom->createElement('apellido',$_POST["apellido"]);
    $fechaNacimiento = $dom->createElement('fechaNacimiento',$_POST["fechaNacimiento"]);
    $email = $dom->createElement('email',$_POST["email"]);
    $contrasena = $dom->createElement('contrasena',password_hash($_POST["contrasena"], PASSWORD_DEFAULT));

    $root->appendChild($usuario);
    $root->appendChild($nombre);
    $root->appendChild($apellido);
    $root->appendChild($fechaNacimiento);
    $root->appendChild($email);
    $root->appendChild($contrasena);

    $dom->appendChild($root);
    $dom->save($xml_file_name);
}


function nuevaId(){
    $file = simplexml_load_file('../data/id.xml');
    $newId = $file[0]["val"];
    $file[0]["val"] = $newId +1;

    $file->asXML('../data/id.xml');
    return $newId;
}



?>