<?php
    $visitas = simplexml_load_file("data/libro_visitas.xml");

    $visita = $visitas->addChild('visita');

    $id = substr($visitas['ult_id'],0,-1) . strval(intval(substr($visitas['ult_id'],-1)) + 1);
    $fecha = date('Y/m/d H:i');
    
    $visitas['ult_id'] = $id;
    $visita->addAttribute('id',$id);
    $visita->addChild('fecha',$fecha);
    $visita->addChild('nombre', $_POST['nombre']);
    if (isset($_POST['visible']) && !empty($_POST['email'])){
        $visita->addChild('email',$_POST['email']);
    }
    $visita->addChild('comentario',$_POST['comentario']);
    
    $visitas->asXML('data/libro_visitas.xml');

    header('Location: addComentarios.html');
    exit
?>