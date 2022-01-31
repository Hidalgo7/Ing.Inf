<?php
    session_start();
    if(isset($_SESSION["carrito"])){
        for ($i = 0; $i <= count($_SESSION["carrito"]); $i++) {
            if($_SESSION["carrito"][$i]==$_POST["id"]){
                unset($_SESSION["carrito"][$i]);
            }
        }
    }

?>