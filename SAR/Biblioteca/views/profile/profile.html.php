<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="shortcut icon" href="../../public/icon.ico" type="image/x-icon">
    <link rel="stylesheet" href="../../css/includes/navbar.css">
    <link rel="stylesheet" href="../../css/includes/footer.css">
    <link rel="stylesheet" href="../../css/profile.css">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Kings&family=Work+Sans:ital,wght@1,600&display=swap" rel="stylesheet">
    <script src="https://kit.fontawesome.com/6c41c17d75.js" crossorigin="anonymous"></script>
    <?php include_once("../includes/navbarDEP.php"); ?>
    <title>Perfil</title>
</head>
<body>
    <?php
    include_once('../includes/navbar.html.php');
        echo '<div>';
        echo('<h2> Mi perfil </h2>');
        echo('<div class="profile">');
        echo('<img id="profile-pic" src="../../public/profile.webp" alt="Foto de perfil">');
        echo('<div class="profile-info">');
        echo('<p id="user">Usuario: ' . $user->usuario . '</p>');
        echo('<p id="user">Nombre: ' . $user->nombre . '</p>');
        echo('<p id="user">Apellido: ' . $user->apellido . '</p>');
        echo('<p id="email">Email: ' . $user->email . '</p>');
        echo('</div>');
        echo('</div>');
        echo('<h2>Lista de Libros</h2>');
        if(sizeof($libros) > 0){
            foreach($libros as $libro){
            echo('<div class="libroPerfil">');
            echo('<img src="../../public/portadas/' . $libro["id_libro"] . '.jpg" alt="Portada del libro" class="book-cover">' );
            echo('<div><p class="title">' . $libro["titulo"] .'</p>');
            echo('<p class="author">' . $libro["autor"] . '</p>');
            echo('<p class="description">' . $libro["descripcion"] . '</p>');
            echo('<p class="price">' . $libro["precio"] . '$</p>');
            echo('</div></div>');
            }
        }
        else{
            echo('<div class="emptyDad"><p id ="empty">Ooops, todavía no tienes ningún libro.<br>');
            echo('Echa un vistazo a nuestro <a href="../catalogo">Catálogo</a></p></div>');
        }
        echo '</div>';
    include_once('../includes/footer.html.php');
    ?>
</body>
</html>