function HomeView(props){
    return(
        <div><center>
            <button  onClick = {event => window.location.hash = "#about"} >
                press this button to turn on the Sommarljusstake</button>
        </center>
        </div>
    )
}
