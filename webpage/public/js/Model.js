// module.exports =
    class Model {
    constructor(observers = []) {
        this.observers = [];
        this.currentUser = null;
        this.currentUsername = null;
        this.lightOn = false;
        this.pendingMessage = false;
        this.morseText = "yeshello";
        this.dimmer = 25;
        this.dimmerShow = 10;
        this.blinkTimer = 10;
        this.blinkSent = false;
        this.blinkOptions = [5, 15, 30, 60];
    }

    setLight(input) {
        this.lightOn = input;
        this.setPendingMessage(false);
        this.notifyObservers();
    }

    signInEmail(email, password) {
        firebase.auth().signInWithEmailAndPassword(email, password)
            .then((userCredential) => {
                // Signed in
                let user = userCredential.user;
                //console.log("User signed in")
                console.log(user);
                this.currentUser = user;
                this.notifyObservers();
                window.location.hash = "#controls";
            })
            .catch((error) => {
                let errorCode = error.code;
                let errorMessage = error.message;
                console.log(errorCode);
                console.log(errorMessage);
                alert(errorMessage);
            });
    }

    signOut() {
        firebase.auth().signOut().then(() => {
            console.log("Signed out")
            this.currentUser = null;
            this.notifyObservers();
            //window.location.hash="#home";
        }).catch((error) => {
            console.log(error);
        });
    }

    addObserver(callback) {
        this.observers = [...this.observers, callback];
    }

    removeObserver(callback) {
        this.observers = this.observers.filter(cb => cb !== callback)
    }

    notifyObservers() {
        this.observers.forEach(cb => {
            setTimeout(() => {
                try {
                    cb()
                } catch (e) {
                    console.log(e)
                }
            }, 0)
        })
    }

    setMorse(plaintext) {
        this.morseText = plaintext;
        console.log("Setting morse text")
        this.notifyObservers();
    }

    setPendingMessage(bool) {
        this.pendingMessage = bool;
        console.log("Setting morse bool")
    }

    setDimmer(input) {
        this.dimmerShow = input;
        this.dimmer = Math.floor(input/100 * 255);
        this.setPendingMessage(false);
        this.notifyObservers();
    }

    setBlinkTimer(time) {
        this.blinkTimer = parseInt(time);
        this.blinkSent = true;
        console.log(time);
        this.setPendingMessage(false);
        this.notifyObservers();
    }

}