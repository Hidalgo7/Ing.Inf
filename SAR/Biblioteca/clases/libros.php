<?php
include_once "conexion.php";

class libroClass {
    protected $ID;
    protected $Titulo;
    protected $Autor;
    protected $Precio;
    protected $Genero;
    
    public function getID()
    {
        return $this->ID;
    }

    public function setID($ID)
    {
        $this->ID = $ID;
        return $this;
    }

    public function getTitulo()
    {
        return $this->Titulo;
    }

    public function setTitulo($Titulo)
    {
        $this->Titulo = $Titulo;
        return $this;
    }

    public function getAutor()
    {
        return $this->Autor;
    }

    public function setAutor($Autor)
    {
        $this->Autor = $Autor;
        return $this;
    }

    public function getPrecio()
    {
        return $this->Precio;
    }

    public function setPrecio($Precio)
    {
        $this->Precio = $Precio;
        return $this;
    }
    
    public function getGenero()
    {
        return $this->Genero;
    }
 
    public function setGenero($Genero)
    {
        $this->Genero = $Genero;
        return $this;
    }
    
    function getLibroList()
    {
        $conexion = new conexion();
        $libros = $conexion->query("SELECT * FROM `catalogo`");
        unset($conexion);

        return $libros;

    }
}