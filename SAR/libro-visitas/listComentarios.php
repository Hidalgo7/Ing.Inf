<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <link rel="stylesheet" type="text/css" href="CSS/styles.css"/>
    <link rel="shortcut icon" href="public/favicon.ico" type="image/x-icon">
    <title>Consultar Comentarios</title>
</head>
<body>
<header>
    <h1> LIBRO DE VISITAS </h1>
    <nav>
        <ul id="ul1">
                <li id="li1"> <a href=addComentarios.html> Añadir comentario </a></li>
                <li id="li2"> <a href=listComentarios.php>Consultar comentarios </a></li>
                <li id="li0"> <a href=index.html> Menu principal </a></li>
        </ul>
    </nav>
    </header>
    <br>

    <?php
        $N = 50;
        $visitas = simplexml_load_file("data/libro_visitas.xml");
        foreach($visitas->visita as $visita){
            echo('<div class="comentario">');
            echo('<div class="header-comentario">');
            echo('<p>' . $visita->fecha . '</p>');
            echo('<h2>' . $visita->nombre . '</h2>');
            if($visita->email != null){
                echo('<p>' . $visita->email . '</p>');
            }
            echo('</div>');
            echo('<div class="texto-comentario">');
            if(strlen($visita->comentario) > 50){
                echo('<p>' . substr($visita->comentario,0,$N) . '... </p>');
                echo('<a href="javascript:mostrarComentario()">[Leer Más]</a>');
            }
            else{
                echo('<p>' . $visita->comentario . '</p>');
            }
            echo('</div>');
            echo('</div>');
        }
    ?>
</body>
</html>