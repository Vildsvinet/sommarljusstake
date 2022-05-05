function HomeView(props) {
    let sneaky;
    if (props.currentUser == null) {
        sneaky = ""
    } else sneaky = "hidden";

    let reverseSneaky;
    if (!(props.currentUser == null)) {
        reverseSneaky = ""
    } else reverseSneaky = "hidden";

    return <div>
        <img src={"midsommarljusstake.png"} alt={"logo"}/>

        <button id={sneaky} className="" onClick={() => window.location.hash = "#login"}>sign in</button>
        <button id={reverseSneaky} className="" onClick={() => window.location.hash = "#controls"}>controls</button>
        <br/>
        <button id={reverseSneaky} className="" onClick={() => props.signOut()}>sign out</button>
        <br/>
        <button onClick={() => window.location.hash = "#about"}>about</button>

    </div>
}
