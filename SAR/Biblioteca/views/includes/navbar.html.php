   <nav>
       <a href="../home">
            <img src="../../public/header-logo.webp" alt="Logo Libreria" id="header-logo"/>
            <p>Libreria Cervantes</p>
        </a>

        <div id="links">
            <a href="../home" class="link">INICIO</a>
            <a href="../catalogo" class="link">CATALOGO</a>
            <a href="../comments/listComentarios.php" class="link">COMENTARIOS</a>
            <a href="../profile" class="link link-perfil">PERFIL</a>

        </div>

        <div id="inicio-sesion">
            <div id="botIniciarSesion">Iniciar Sesion</div>
            <div id="botRegistro">Registrarse</div>
        </div>

        <div id="navUsuario">
            <div id="carrito">
                <div id="numLibros">0</div>
                <div id="listado">
                    <div id="libros">
                        No hay ningun libro añadido
                    </div>
                    <div id="precioTotal">

                    </div>
                    <div id="contBotComprar">
                        <div id="botComprar">Comprar</div>
                    </div>
                </div>
            </div>
            <img alt="Imagen de perfil del usuario en navegador" src="../../public/profile.webp">
            <p id="navNombreUsuario"><?php
                if(!isset($_SESSION["usuario"])){
                    session_start();
                }
                if(isset($_SESSION["usuario"])){
                    echo $_SESSION["usuario"];
                }
            ?>
            </p>
            <div id="botCerrarSesion">Cerrar Sesion</div>
        </div>


       <div id="pop">
           <div id="popMain">
               <form id="popRegistro">
                   <div class="popTitulo">Nuevo Registro</div>
                   <label>
                       <p>Usuario</p>
                       <input type="text" id="regUsuario">
                   </label>
                   <label>
                       <p>Nombre</p>
                       <input type="text" id="regNombre">
                   </label>
                   <label>
                       <p>Apellido</p>
                       <input type="text" id="regApellido">
                   </label>
                   <label>
                       <p>Fecha de nacimiento</p>
                       <input type="date" min='1899-01-01' max='2021-12-09' id="regNacimiento" >
                   </label>
                   <label>
                        <p>Email</p>
                       <input type="text" id="regEmail">
                   </label>
                   <label>
                        <p>Repetir Email</p>
<!--                       <input type="text" onpaste="return false;" autocomplete="nope" id="regREmail">-->
                       <input type="text" id="regREmail">
                   </label>
                   <label>
                        <p>Contraseña</p>
                       <input type="password"  id="regContrasena">
                   </label>
                   <button id="regEnviarR">Enviar</button>
               </form>
               <form id="popIniciarSesion">
                   <div class="popTitulo">Iniciar Sesion</div>
                   <label>
                       <p>Usuario</p>
                       <input type="text" id="ISUsuario">
                   </label>
                   <label>
                       <p>Contraseña</p>
                       <input type="password" id="ISContrasena">
                   </label>
                   <button id="regEnviarIS">Enviar</button>
               </form>
           </div>
       </div>
    </nav>
