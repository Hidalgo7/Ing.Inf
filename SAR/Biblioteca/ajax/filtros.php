<?php
    session_start();
    include_once "../clases/conexion.php";
    $conexion = new conexion();

    $inputTitulo = $_POST['inputTitulo'];
    $inputAutor = $_POST['inputAutor'];
    $inputGenero = $_POST['inputGenero'];
    $inputPrecio = $_POST['inputPrecio'];


    $result = $conexion->query("SELECT * FROM `catalogo`
                                WHERE titulo LIKE '%$inputTitulo%' AND autor LIKE '%$inputAutor%' AND genero LIKE '%$inputGenero%'
                                ORDER BY precio $inputPrecio;");

    
    foreach ($result->fetchAll() as $libro) {
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
  

?>