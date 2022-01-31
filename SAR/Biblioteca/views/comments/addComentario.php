<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Añadir comentarios</title>
    <link rel="stylesheet" href="../../css/comments.css">
    <script src="../../js/script.js"></script>
    <?php include_once("../includes/navbarDEP.php");?>
</head>
<body>

<?php
include_once('../includes/navbar.html.php');
?>

<br>
<div class="addComentario">
    <div class="header-formulario">
        <p>AÑADIR COMENTARIO</p>
    </div>
    <form id="formAddComentario" action="guardarComentario.php" onsubmit="return verify()" method="post">
        <br>
        <input type="text" name="nombre"   id="nombre"  placeholder="Username*">
        <textarea id="comentario" name="comentario"  rows="4" cols="50"  placeholder="Add comment*"></textarea>
        <input type="submit" name="submit1" value="Enviar">
    </form>
</div>
</body>
</html>