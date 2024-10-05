



//localStorige //classList
function setBackground(color) {
    if (color === 'blue') {
        document.body.classList.remove('green');
        document.body.classList.add('blue');
    } else if (color === 'green') {
        document.body.classList.remove('blue');
        document.body.classList.add('green');
    }
    else if (color === 'original') {
        document.body.classList.remove('blue');
        document.body.classList.remove('green');
    }

    
    //getComputedStyle
    let background = getComputedStyle(document.body);
    console.log(background.backgroundColor);

    // Salvare preferință în localStorage
    localStorage.setItem('color', color);
}
// Verificare și încărcare preferință din localStorage la încărcarea paginii
document.addEventListener('DOMContentLoaded', () => {
    const savedColor = localStorage.getItem('color');
    if (savedColor) {
        setBackground(savedColor);
    }
});

//Random
function RandomBackground() {
    const currrentColor = document.body.style.backgroundColor;
    // Generez valori RGB aleatoare între 0 și 255
    let r = Math.floor(Math.random() * 256); //random()= val aleatoare intre 0 si <1
    let g = Math.floor(Math.random() * 256);
    let b = Math.floor(Math.random() * 256);

    // Constr culoarea RGB
    let randomColor = `rgb(${r}, ${g}, ${b})`;

    document.body.style.backgroundColor = randomColor;
    setTimeout(() => {
        document.body.style.backgroundColor = currrentColor;
    }, 3000);
}

function InchideReclama() {
    let reclama = document.getElementById('reclama');
    let buton = document.getElementById('inchideReclama');
    if (reclama) {
        reclama.remove();
        buton.remove();
    }
}

window.onload = function() 
{
    let inchideReclama = document.getElementById('inchideReclama');
    inchideReclama.addEventListener('click', InchideReclama);
    inchideReclama.style.backgroundColor = "brown";
    inchideReclama.style.color = "white";



    const form = document.getElementById('form');
    const username = document.getElementById('username');
    const email = document.getElementById('email');
    const password = document.getElementById('password');
    const password2 = document.getElementById('password2');
    const tara = document.getElementById('tara');
    const mesaj = document.getElementById('mesaj');
   
    

    form.addEventListener('submit', e => {
        e.preventDefault(); // Previne trimiterea formularului și reîncărcarea paginii
        validateInputs();

       
        
        //POST
        // var myform = document.getElementById("form");
        // myform.onsubmit = function (event) {
        //   event.preventDefault();
      
        //   var data = {
        //     username: document.getElementById('username'),
        //     email : document.getElementById('email'),
        //     password : document.getElementById('password'),
        //     password2 : document.getElementById('password2'),
        //     tara : document.getElementById('tara'),
        //     mesaj : document.getElementById('mesaj'),
        //   };
      
        //   fetch("http://localhost:8000", {
        //     method: "post",
        //     headers: { "Content-Type": "application/json" },
        //     body: JSON.stringify(data),
        //   })
        //     .then(function (response) {
        //       return response.status;
        //     })
        //     .then(function (status) {
        //       alert(status);
        //     });
        // };
        
        //GET
        fetch("formular.json")
            .then(function (response) {
                return response.text();
            })
            .then(function (data) {
                console.log(data);
            })
            .catch(function (error) {
                console.error("Eroare:", error);
            });

            const username=document.getElementById("username").value;
            const password= document.getElementById("password").value;
            
            fetch("users.json")
                .then((response) => {
                    return response.json()})
                .then((users) => {
                    const userExists=users.some(
                        (user) => user.username === username && user.password === password
                    );
                    if( userExists) {
                        sessionStorage.setItem("username", username);
                        alert("Autentificare reusita");
                        sessionStorage.setItem("showLogout", "true");
                        let modificari = {
                            run: function(){
                                let formular = document.getElementById("form");
                                formular.remove();
                                let button = document.createElement("button");
                                button.textContent = "Logout";
                                button.setAttribute("id", "button-logout");
                                let container = document.getElementsByClassName("container")[0];
                                container.appendChild(button);
                            }
                        };
                        modificari.run();
                        // setTimeout
                        setTimeout(function() {
                            window.location.href ="PROIECT.html";
            
                        }, 500);
            
                    } else {
                        window.location.href = "404.html";
                    }
                })
                .catch((error) => {
                    console.error("Eroare la preluarea listei de utilizatori:", error)
                });
    });

    form.addEventListener('keydown', e => {
        if(e.key === 'Enter') {
        e.preventDefault(); // Previne trimiterea formularului și reîncărcarea paginii
        validateInputs();

        //GET
        fetch("formular.json")
            .then(function (response) {
                return response.text();
            })
            .then(function (data) {
                console.log(data);
            })
            .catch(function (error) {
                console.error("Eroare:", error);
            });

            const username=document.getElementById("username").value;
            const password= document.getElementById("password").value;
            
            fetch("users.json")
                .then((response) => {
                    return response.json()})
                .then((users) => {
                    const userExists=users.some(
                        (user) => user.username === username && user.password === password
                    );
                    if( userExists) {
                        sessionStorage.setItem("username", username);
                        alert("Autentificare reusita");
                        sessionStorage.setItem("showLogout", "true");
                        let modificari = {
                            run: function(){
                                let formular = document.getElementById("form");
                                formular.remove();
                                let button = document.createElement("button");
                                button.textContent = "Logout";
                                button.setAttribute("id", "button-logout");
                                let container = document.getElementsByClassName("container")[0];
                                container.appendChild(button);
                            }
                        };
                        modificari.run();
                        
                        setTimeout(function() {
                            window.location.href ="PROIECT.html";
            
                        }, 500);
            
                    } else {
                        window.location.href = "404.html";
                    }
                })
                .catch((error) => {
                    console.error("Eroare la preluarea listei de utilizatori:", error)
                });
            }
    });
    
    const setError = (element, message) => {
        const inputControl = element.parentElement;
        const errorDisplay = inputControl.querySelector('.error');

        errorDisplay.innerText = message;
        inputControl.classList.add('error');
        inputControl.classList.remove('success')
    }

    const setSuccess = element => {
        const inputControl = element.parentElement;
        const errorDisplay = inputControl.querySelector('.error');

        errorDisplay.innerText = '';
        inputControl.classList.add('success');
        inputControl.classList.remove('error');
    };

    const isValidEmail = email => {
        const re = /^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
        return re.test(String(email).toLowerCase());
    }

    const validateInputs = () => {
        const usernameValue = username.value.trim(); //elimina spațiile albe
        const emailValue = email.value.trim();
        const passwordValue = password.value.trim();
        const password2Value = password2.value.trim();

        if(usernameValue === '') {
            setError(username, 'Username-ul este obligatoriu');
        } else {
            setSuccess(username);
        }

        if(emailValue === '') {
            setError(email, 'Email-ul este obligatoriu');
        } else if (!isValidEmail(emailValue)) {
            setError(email, 'Introduceti un email valid');
        } else {
            setSuccess(email);
        }

        if(passwordValue === '') {
            setError(password, 'Parola este obligatorie.');
        } else if (passwordValue.length < 8 ) {
            setError(password, 'Parola trebuie sa contina minim 8 caractere.')
        } else {
            setSuccess(password);
        }

        if(password2Value === '') {
            setError(password2, 'Confirmarea parolei.');
        } else if (password2Value !== passwordValue) {
            setError(password2, "Parolele nu se potrivesc.");
        } else {
            setSuccess(password2);
        }

    };

    //Setinterval // selector CSS
    let reclama = document.querySelector("#reclama");
    let mesaje = ['Welcome to our website!', 'Check out our new products!', 'Subscribe for updates!'];
    let index = 0;
    reclama.style.color = "brown";
    setInterval(() => {
        index = (index + 1) % mesaje.length;
        reclama.textContent = mesaje[index];
    }, 3000);

    document.getElementById('randomButton').addEventListener('click', RandomBackground);
}

document.addEventListener('DOMContentLoaded', () => {
        const showLogout = sessionStorage.getItem("showLogout");
        if ( showLogout === "true") {
            let formular = document.getElementById("form");
            formular.remove();
            let button = document.createElement("button");
            button.textContent = "Logout";
            button.setAttribute("id", "button-logout");
            let container = document.getElementsByClassName("container")[0];
            container.appendChild(button);

            document.getElementById("button-logout").addEventListener("click",()=>{
                sessionStorage.clear();
                window.location.href="/PROIECT.html";
            });
        }
    });

