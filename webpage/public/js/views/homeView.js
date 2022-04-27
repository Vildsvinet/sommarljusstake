function HomeView(props){
    let sneaky;
    if (props.currentUser == null) {
        sneaky = ""
    }
    else sneaky = "hidden";

    let reverseSneaky;
    if (!(props.currentUser == null)) {
        reverseSneaky = ""
    }
    else reverseSneaky = "hidden";

    return <div>
        <center>
            <button  onClick = {() => window.location.hash = "#about"}>About us</button>
            <button onClick = {() => props.setLight(true)}>ON</button>
            <button onClick = {() => props.setLight(false)}>OFF</button>
        </center>

        <button id={sneaky} className="" onClick={() => window.location.hash="#login"}>ACCOUNT</button>
        <button id={reverseSneaky} className="" onClick={() => props.signOut()}>SIGNOUT</button>
    </div>

}
