function ControlsView(props) {
    return (
        <div>
            <center>
                <button>clickme</button><br/>
                <label>Text to blink:</label>
                <input type="text"
                        onInput={event=>props.onMorseText(event.target.value)}/>
            </center>
        </div>
    )
}