function ControlsView(props) {
    let status;
    if (props.lightStatus == true) {
        status = "ON";
    } else {status = "OFF"}

    return (
        <div>
            <center>
                Status: {status}
                <br/>
                <button disabled={props.lightStatus} onClick = {() => props.setLight(true)}>ON</button>
                <button disabled={!props.lightStatus} onClick = {() => props.setLight(false)}>OFF</button>
                <br/>
                <br/>
                <label>Text to morse:</label>
                <input type="text" placeholder="Enter text" onInput={event=>props.onMorseText(event.target.value)}/>
                {console.log(props.morseText)}
                <button type={"submit"} onClick={()=> {props.setMorse()}}>Submit</button>
                <br/>
                <button onClick = {() => window.location.hash = "#home"}>Back to home</button>
            </center>
        </div>
    )
}