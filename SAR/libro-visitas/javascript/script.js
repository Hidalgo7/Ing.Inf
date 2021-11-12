function verify(){
    var nombre = document.getElementById("nombre").value
    var correo = document.getElementById("correo").value
    var checkbox = document.getElementById("visible")
    var comentario = document.getElementById("comentario").value
    
    if( nombre == ""){
        alert("No has introducido tu nombre.")
    }
    else if( comentario == ""){
        alert("No has añadido ningun comentario.")
    }
    if (correo){
        var lista = correo.split("@")
        if(lista.length > 1){
            if (lista[0].length >= 1 && lista[1].includes(".")){
                if (lista[1].split(".")[1].length >= 2){
                    alert("Direccion de correo valida.")
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
    return false
}