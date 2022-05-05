class Model {
    constructor(observers = []) {
        this.observers = [];
        this.currentUser = null;
        this.currentUsername = null;
        this.lightOn = false;
        this.morseText = "yeshello";
    }

    setLight(input) {
        this.lightOn = input;
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
                window.location.hash="#controls";
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
        this.observers.forEach(cb =>
        {setTimeout(()=>{
            try{
                cb()}catch (e) {console.log(e)}},0)})
    }

    setMorse(plaintext){
        this.morseText = plaintext;
        this.notifyObservers();
    }

}