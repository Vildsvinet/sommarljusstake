function ControlsView(props) {
    return (
        <div>
            <center>
                <button onClick = {() => props.setLight(true)}>ON</button>
                <button onClick = {() => props.setLight(false)}>OFF</button>

                <br/>
                <label>Text to blink:</label>
                <input type="text"
                       onInput={event=>props.onMorseText(event.target.value)}/>
                <br/>
                <button>Submit</button>
                <br/>
                <button onClick = {() => window.location.hash = "#home"}>Back to home</button>
            </center>
        </div>
    )
}