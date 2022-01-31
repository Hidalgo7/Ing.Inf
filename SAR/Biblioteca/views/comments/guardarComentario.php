<?php
    $comentarios = simplexml_load_file("../../data/comments/comments.xml");

    $comentario = $comentarios->addChild('comentario');

    $id = substr($comentarios['ult_id'],0,-1) . strval(intval(substr($comentarios['ult_id'],-1)) + 1);
    $fecha = date('Y/m/d H:i');
    $comentarios['ult_id'] = $id;
    $comentario->addAttribute('id',$id);
    $comentario->addChild('fecha',$fecha);
    $comentario->addChild('nombre', $_POST['nombre']);
    $comentario->addChild('texto',$_POST['comentario']);
    
    $comentarios->asXML('../../data/comments/comments.xml');

    header('Location: listComentarios.php');


?>