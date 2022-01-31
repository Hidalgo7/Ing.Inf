$(document).ready(function(){
    noEnviarForms();
    comprobarLogin();
    interaccionPopUp();
    addNuevoUsuario();
    botonComprar();
    botonQuitarLibro();
    iniciarSesion();
    cerrarSesion();

});


function botonQuitarLibro(){
    $("#libros").on("click",".quitarLibro",function(e){

        var idLibroC = $(this).parent().attr("id")
        var idLibro =  idLibroC.substr(3,idLibroC.length-1);
        $.ajax({
            url: "../../ajax/navbar_quitarLibroCesta.php",
            data: {"id":idLibro},
            type: "POST",
            success: function (data) {
                $("#"+idLibroC).remove();
                $("#precioTotal").html("");
                $("#numLibros").html(0);
            },
            errro: function (error) {
                console.log("navbar_addLibroCesta.php ---->");
                console.log(error);
            }
        });
    })
}

function botonComprar(){
    $("#botComprar").click(function(){
        comprar();
    });
}
function comprar(){
    $.ajax({
        url: "../../ajax/navbar_completarCompra.php",
        type: "GET",
        success: function (data) {
            console.log(data);
            notCorrecto("Compra realizada!");
            sleep(1000).then(() => {
                location.reload();
            });
        },
        errro: function (error) {
            console.log("navbar_addLibroCesta.php ---->");
            console.log(error);
        }
    });
}
function sleep (time) {
    return new Promise((resolve) => setTimeout(resolve, time));
}
function addLibroCesta(id){
    $.ajax({
        url: "../../ajax/navbar_addLibroCesta.php",
        data: {"id":id},
        type: "POST",
        success: function (data) {
            cargarLibrosCesta();
            notCorrecto("Libro añadido!");
        },
        errro: function (error) {
            console.log("navbar_addLibroCesta.php ---->");
            console.log(error);
        }
    });
}
function cargarLibrosCesta(){
    var libro;
    $.ajax({
        url: "../../ajax/navbar_getLibrosCesta.php",
        type: "POST",
        dataType: "json",
        success: function (data) {
            $("#libros").empty();
            let cant = 0;
            let total = 0;
            let partes;
            var precio;
            if(typeof data == "object"){
                data.forEach(libro => {
                    precio = libro["precio"];
                    libro = '<div class="libro" id="lId'+libro["id"]+'">\n' +
                        '       <div class="tituloLibro">'+libro["titulo"]+'</div>\n' +
                        '       <div class="autorLibro">'+libro["autor"]+'</div>\n' +
                        '       <div class="precioLibro">'+libro["precio"]+'</div>\n' +
                        '       <div class="quitarLibro">X</div>\n' +
                        '   </div>';
                    cant++;
                    partes = precio.split(".");

                    total += parseInt(partes[0])+parseInt(partes[1])/100;
                    $("#libros").append(libro);
                });
                $("#numLibros").html(cant);

                total = parseFloat(total).toFixed(2);
                $("#precioTotal").html("Precio total : "+total+"$");
            }


        },
        errro: function (error) {
            console.log("navbar_addLibroCesta.php ---->");
            console.log(error);
        }
    });
}

function comprobarLogin(){
    if($("#navNombreUsuario").html().trim()!=""){
        $("#navUsuario").css("display","grid");
        $(".link-perfil").css("display","grid");
        cargarLibrosCesta();
    }else{
        $("#inicio-sesion").css("display","grid");
    }
}


function noEnviarForms(){
    $("#popRegistro").submit(function(e){
        e.preventDefault();
    });
    $("#popIniciarSesion").submit(function(e){
        e.preventDefault();
    });
}
function mostrarOpciones(){
    $("#inicio-sesion").css("display","grid");
    $("#navUsuario").css("display","none");
}

function mostrarUsuario(usuario){
    console.log(usuario);
    $("#inicio-sesion").css("display","none");
    $("#navUsuario").css("display","grid");
    $("#navNombreUsuario").html(usuario);
}

function interaccionPopUp(){
    cerrarPopUp();
    abrirPopUp();
}
function abrirPopUp(){
    $("#botIniciarSesion").click(function(){
        $("#popIniciarSesion").css("display","grid");
        $("#pop").css("display","grid");
    });

    $("#botRegistro").click(function(){
        $("#popRegistro").css("display","grid");
        $("#pop").css("display","grid");
    });


}

function cerrarPopUp(){
    $("#pop").on("click",function(){
        $("#popIniciarSesion").css("display","none");
        $("#popRegistro").css("display","none");
        $("#pop").css("display","none");
    });

    $("#pop div").click(function(e) {
        e.stopPropagation();
    });
}
function ocultarPopUp(){
    $("#pop").css("display","none");
}

function iniciarSesion(){
    $("#regEnviarIS").click(function () {
        var usuario = $("#ISUsuario").val();
        var contrasena = $("#ISContrasena").val();
        var usuario = {
            "usuario": usuario,
            "contrasena": contrasena
        };

        $.ajax({
            url: "../../ajax/navbar_iniciarSesion.php",
            data: usuario,
            type: "POST",
            success: function (data) {
                if(data=="OK"){
                    notCorrecto("Sesion Iniciada!")
                    mostrarUsuario(usuario.usuario);
                    ocultarPopUp();
                    $(".link-perfil").css("display","grid");

                } else{
                    notError(data);
                }
            },
            errro: function (error) {
                console.log("navbar_iniciarSesion.php ---->");
                console.log(error);
            }
        });
    });
}


function addNuevoUsuario() {
    $("#regEnviarR").click(function () {
        var usuario = $("#regUsuario").val();
        var nombre = $("#regNombre").val();
        var apellido = $("#regApellido").val();
        var fechaNacimiento = $("#regNacimiento").val();
        var email = $("#regEmail").val();
        var rEmail = $("#regREmail").val();
        var contrasena = $("#regContrasena").val();
        var usuario = {
            "usuario": usuario,
            "nombre": nombre,
            "apellido": apellido,
            "fechaNacimiento": fechaNacimiento,
            "email": email,
            "rEmail": rEmail,
            "contrasena": contrasena
        };

        console.log(usuario);
        $.ajax({
            url: "../../ajax/navbar_nuevoUsuario.php",
            data: usuario,
            type: "POST",
            success: function (data) {
                if(data=="OK"){
                    notCorrecto("Usuario Creado correctamente!");
                    mostrarUsuario(usuario.usuario);
                    ocultarPopUp();
                } else{
                    notError(data);
                }
            },
            errro: function (error) {
                console.log("navbar_nuevoUsuario.php ---->");
                console.log(error);
            }
        });
    });
}

function cerrarSesion(){
    $("#botCerrarSesion").on("click",function () {
        $.ajax({
            url: "../../ajax/navbar_cerrarSesion.php",
            type: "GET",
            success: function (data) {
                if(data=="OK"){
                    notCorrecto("Sesion Cerrada Correctamente!")
                    mostrarOpciones();
                    $(".link-perfil").css("display","none");

                } else{
                    notError(data);
                }
            },
            errro: function (error) {
                console.log("navbar_cerrarSesion.php ---->");
                console.log(error);
            }
        });
    });
}
const myNotificationErr = window.createNotification({
    // close on click
    closeOnClick: true,

    // displays close button
    displayCloseButton: false,

    // nfc-top-left
    // nfc-bottom-right
    // nfc-bottom-left
    positionClass: 'nfc-top-right',

    // callback
    onclick: false,

    // timeout in milliseconds
    showDuration: 3500,

    // success, info, warning, error, and none
    theme: 'error'
});
const myNotificationCorrecto = window.createNotification({
    // close on click
    closeOnClick: true,

    // displays close button
    displayCloseButton: false,

    // nfc-top-left
    // nfc-bottom-right
    // nfc-bottom-left
    positionClass: 'nfc-top-right',

    // callback
    onclick: false,

    // timeout in milliseconds
    showDuration: 3500,

    // success, info, warning, error, and none
    theme: 'success'
});

function notCorrecto(mensaje){
    myNotificationCorrecto({
        title: 'Completado',
        message: mensaje
    });
}

function notError(mensaje){
    myNotificationErr({
        title: 'Error',
        message: mensaje
    });
}