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
            <button id={sneaky} className="" onClick={() => window.location.hash="#login"}>Sign in</button>
            <button id={reverseSneaky} className="" onClick={() => window.location.hash = "#controls"}>Controls</button>
            <br/>
            <button id={reverseSneaky} className="" onClick={() => props.signOut()}>Sign out</button>
            <br/>
            <button onClick = {() => window.location.hash = "#about"}>About</button>

        </center>



    </div>

}
