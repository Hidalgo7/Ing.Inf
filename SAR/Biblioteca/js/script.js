function verify(){
    var nombre = document.getElementById("nombre").value
    var comentario = document.getElementById("comentario").value
    var send = false

    if(nombre == ""){
        alert("No has introducido tu nombre.")
    }
    else if(comentario == ""){
        alert("No has añadido ningun comentario.")
    }
    else{
        send = true
    }
    return send
}