<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <?php
    include_once "../includes/navbarDEP.php";
    ?>
    <link rel="stylesheet" href="../../css/catalogo.css">
    <script src="../../js/catalogo.js"></script>
    <title>Cat&aacutelogo</title>
</head>
<body>
    <?php
    include_once "../includes/navbar.html.php";
    ?>
    <div class="content">
        <div class="filtros">
            <h1>Filtros</h1>
            <div class="filtroTitulo">
                <h4>Titulo</h4>
                <input type="text" name="filtroTitulo" id="inputTitulo">
            </div>
            <div class="filtroAutor">
                <h4>Autor</h4>
                <input type="text" name="filtroAutor" id="inputAutor">
            </div>
            <div class="filtroGenero">
                <h4>G&eacutenero</h4>
                <input type="text" name="filtroGenero" id="inputGenero">
            </div>
            <div class="filtroPrecio">
                <h4>Precio</h4>
                <div>
                    <label>
                        <input type="radio" name="filtroPrecio" id="ASC" checked>
                        <div>Ascendente</div>
                    </label>
                </div>
                <div>
                    <label>
                        <input type="radio" name="filtroPrecio" id="DESC">
                        <div>Descendente</div>
                    </label>

                </div>
            </div>
        </div>

        <div class="listaLibros">
            <?php
            foreach ($listaLibros as $libro) {
                echo '
                <div class="libro">
                    <img src="../../public/portadas/' . $libro['id'] . '.jpg" alt="Portada del libro" class="book-cover">
                    <div class="informacion">
                        <div class="contTitulo">
                            <h3 class="title">' . $libro['titulo'] . '</h3>
                            <p class="author">' . $libro['autor'] . '</p>
                        </div>
                        <p class="description">' . $libro['descripcion'] . '</p>
                        <div class="contCompra">
                        ';
                        if (isset($_SESSION["usuario"])) {
                            echo '<input type="button" value="Comprar libro ' . $libro['precio'] . '$" class="comprarLibro" id="' . $libro['id'] .'" ></input>';
                        }
                        echo '
                        </div>
                    </div>
                </div>';
            }

            /*
            foreach ($listaLibros as $libro) {
                echo '<div class="libro">
                <img src="../public/portadas/libro' . $libro['id'] . '.webp" alt="Portada del libro" class="book-cover">
                
                <h3 class="title">' . $libro['titulo'] . '</h3>
                <p class="author">' . $libro['autor'] . '</p>
                <p class="description">' . $libro['descripcion'] . '</p>
                <input type="button" value="Comprar" class="comprarLibro" id="' . $libro['id'] .'" ></input>
                <p class="price">' . $libro['precio'] . ' $</p></div>';
            }
            */
            ?>
        </div>
    </div>
    <div id="footer">
    
    </div>

</body>

</html>


<php ?>