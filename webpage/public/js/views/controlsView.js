function ControlsView(props) {
    let status;
    if (props.lightStatus === true) {
        status = "ON";
    } else {
        status = "OFF"
    }

    let sneaky;
    if (props.lightStatus === true) {
        sneaky = ""
    } else sneaky = "hidden";

    let reverseSneaky;
    if (!(props.lightStatus === true)) {
        reverseSneaky = ""
    } else reverseSneaky = "hidden";

    return (
        <div>
            <center>
                Status: {status}
                <br/>
                <br/>
                <label className="switch">
                    <input className="inputToggle" type="checkbox" checked={props.lightStatus} onChange={() => props.setLight(!props.lightStatus)}/>
                    <span className="sliderToggle rounded"></span>
                </label>
                <br/>
                <label>Text to morse:</label>
                <input className="inputMorse" type="text" pattern="[0-9a-öA-Ö ]+$" placeholder="Enter text"
                       onInput={event => {
                           props.onMorseText(event.target.value);
                           props.setPendingMessage(true)
                       }}/>
                <button type={"submit"} onClick={() => {
                    props.setMorse()
                }}>Submit
                </button>
                <br/>
                <br/>
                <div className={"slidecontainer"}>
                    <input type="range" min="5" max="100" value={props.dimmerShow} className="slider"
                           onInput={event => props.onMoveDimmer(event.target.value)}/>
                    <p>Dimmer: {props.dimmerShow} percent</p>
                </div>
                <br/>
                <button onClick={() => window.location.hash = "#home"}>Back to home</button>
            </center>
        </div>
    )
}

/* Old button, in case toggle doesn't work as intended
                Turn
                <button id={reverseSneaky} disabled={props.lightStatus} onClick={() => props.setLight(true)}>ON</button>
                <button id={sneaky} disabled={!props.lightStatus} onClick={() => props.setLight(false)}>OFF</button>
                the Sommarljusstake
                <br/>
 */