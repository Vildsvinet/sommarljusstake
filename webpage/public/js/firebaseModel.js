function persistModel(model) {
    let loadingFromFirebase=false;
    model.addObserver(function(){
        setDataToFirebase();
    });

    // TODO Stoppa overwrite till default settings som sker vid inloggning från ny enhet
    function setDataToFirebase() {
        if(loadingFromFirebase) return
        if(firebase.auth().currentUser)
            firebase.database().ref("users/" + firebase.auth().currentUser.uid).set({
                lightStatus: model.lightOn,
                morseText: model.morseText

            })
    }

    function setDataFromFirebase() {
        if(firebase.auth().currentUser)
            firebase.database().ref("users/" + firebase.auth().currentUser.uid).once("value", function(data){
                loadingFromFirebase= true;
                try {
                    if(data.val()) {
                        model.setLight(data.val().lightStatus);
                        model.setMorse(data.val().morseText);
                    }
                }
                catch (e) {console.log(e)}
                finally {loadingFromFirebase= false;}
            });
        else console.log("Can't load UID")
    }

    firebase.auth().onAuthStateChanged((user) => {
        if(user) {
            model.currentUser = firebase.auth().currentUser;
            setDataFromFirebase();

        } else  {
            console.log("No user logged in");
        }
    });

}