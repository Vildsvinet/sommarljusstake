function ControlsView(props) {
    let status;
    if (props.lightStatus === true) {
        status = "ON";
    } else {
        status = "OFF"
    }

    return (
        <div>
            <center>
                <br/>
                <br/>

                <div>
                    Status: {status}
                    <br/>
                    <br/>
                    <label className="switch">
                        <input className="inputToggle" type="checkbox"
                               checked={props.lightStatus}
                               onChange={() => props.setLight(!props.lightStatus)}/>
                        <span className="sliderToggle rounded"></span>
                    </label>
                </div>

                <br/>
                <br/>
                <br/>

                <div>
                <label>Text to Morse:</label><br/>
                <input className="inputMorse" type="text" pattern="[0-9a-öA-Ö ]+$" placeholder="Enter text"
                       onInput={event => {
                           props.onMorseText(event.target.value);
                           props.setPendingMessage(true)
                       }}/>
                <button className="smallButton" type={"submit"} onClick={() => {
                    props.setMorse()
                }}>Submit
                </button>
                </div>

                <br/>
                <br/>

                <div>
                Dimmer: {props.dimmerShow} percent <br/><br/>
                    <center>
                <div className={"slideContainer"}>
                    <input type="range" min="5" max="100" value={props.dimmerShow} className="slider"
                           onInput={event => props.onMoveDimmer(event.target.value)}/>
                </div>
                    </center>
                </div>

                <br/>
                <br/>

                <div>
                <p>Duration of random blinking:</p>
                <select onChange = {event => props.setBlinkTimer(event.target.value)}>
                    {props.blinkOptions.map(function(opt){ return <option key={opt}> {opt} </option>})}
                </select> seconds
                </div>

                <br/>
                <br/>
                <br/>
                <div>
                    {/*<button onClick={() => window.location.hash = "#explanations"}>Explanations</button><br/>*/}
                    <button>Explanations</button><br/>
                    <button onClick={() => window.location.hash = "#home"}>Back to Home</button>
                </div>
            </center>
        </div>
    )
}