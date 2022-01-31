<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <link rel="stylesheet" href="../../css/comments.css">
    <title>Consultar Comentarios</title>
    <?php include_once("../includes/navbarDEP.php");?>
</head>
<body>

    <?php
    include_once('../includes/navbar.html.php');
    ?>

    <a href="addComentario.php" class="btn-flotante">Añadir comentario</a>

<br>

    <?php
    $comentarios = simplexml_load_file("../../data/comments/comments.xml");
    foreach($comentarios->comentario as $comentario){
        echo('<div class="comentario">');
        echo('<div class="header-comentario">');
        echo('<p>' . $comentario->fecha . '</p>');
        echo('<h2>' . $comentario->nombre . '</h2>');
        echo('</div>');
        echo('<div class="texto-comentario">');
        echo('<p>' . $comentario->texto . '</p>');
        echo('</div>');
        echo('</div>');
    }
    ?>



</body>
</html>