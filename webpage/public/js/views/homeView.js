function HomeView(props){
    return <div>
        <center>
            <button  onClick = {() => window.location.hash = "#about"}>About us</button>
            <button onClick = {() => props.setLight(true)}>ON</button>
            <button onClick = {() => props.setLight(false)}>OFF</button>
        </center>
    </div>

}
