document.addEventListener("DOMContentLoaded",() =>{
    const userNameDisplay=document.getElementById("username");
    const loggedInUser=sessionStorage.getItem("username");
    if(loggedInUser){
        userNameDisplay.textContent=loggedInUser;
    }else{
        window.location.href="/home.html";
    }
    document.getElementById("logout-button").addEventListener("click",()=>{
        sessionStorage.clear();
        window.location.href="/home.html";
    });

});