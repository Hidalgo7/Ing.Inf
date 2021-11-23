function verify(){
    var nombre = document.getElementById("nombre").value
    var correo = document.getElementById("email").value
    var checkbox = document.getElementById("visible")
    var comentario = document.getElementById("comentario").value
    var send = false
    
    if(nombre == ""){
        alert("No has introducido tu nombre.")
    }
    else if(comentario == ""){
        alert("No has añadido ningun comentario.")
    }
    else if (correo){
        var lista = correo.split("@")
        if(lista.length > 1){
            if (lista[0].length >= 1 && lista[1].includes(".")){
                if (lista[1].split(".")[1].length >= 2){
                    send = true
                }
                else{
                    alert("Direccion de correo no valida.")
                }
            }
            else{
                alert("Direccion de correo no valida.")
            }
        }
        else{
            alert("Direccion de correo no valida.")
        }
    }
    else{
        send = true
    }
    return send
}