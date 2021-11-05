function verify(){
    var nombre = document.getElementById("nombre").value
    var correo = document.getElementById("correo").value
    var checkbox = document.getElementById("visible")
    var comentario = document.getElementById("comentario").value
    
    if( nombre == ""){
        alert("No has introducido tu nombre")
    }
    else if( comentario == ""){
        alert("No has añadido ningun comentario")
    }
}