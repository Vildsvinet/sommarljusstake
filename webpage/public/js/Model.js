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
        this.blinkTimer = 5;
        this.blinkSent = false;
        this.blinkOptions = [5, 15, 30, 60];
    }

    setLight(input) {
        this.lightOn = input;
        this.setPendingMessage(false);
        this.setBlinkSent(false);
        this.notifyObservers();
        //console.log("Setting light to " + input)
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
        this.setBlinkSent(false);
        this.morseText = plaintext;
        //console.log("Setting morse text to " + plaintext)
        this.notifyObservers();
    }

    setPendingMessage(bool) {
        this.pendingMessage = bool;
        //console.log("Setting morse bool to " + bool);
        this.notifyObservers();
    }

    setDimmer(input) {
        this.setBlinkSent(false);
        this.dimmerShow = input;
        this.dimmer = Math.floor(input/100 * 255);
        this.setPendingMessage(false);
        this.notifyObservers();
        //console.log("Setting dimmer to " + input)
    }

    setBlinkTimer(time) {
        this.blinkTimer = parseInt(time);
        this.blinkSent = true;
        //console.log("Set blink timer to " + time);
        this.setPendingMessage(false);
        this.notifyObservers();
    }

    setBlinkSent(bool) {
        this.blinkSent = bool;
        //console.log("Blink status bool set to " + bool)
    }

}