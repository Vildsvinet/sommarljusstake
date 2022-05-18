function ControlsPresenter(props){
    const [lightStatus, setLightStatus]=React.useState(props.model.lightOn);
    const [pendingMessage, setPendingMessage] = React.useState(props.model.pendingMessage);
    const [currentMorseText, setCurrentMorseText] = React.useState(props.model.morseText);
    const [dimmer, setDimmer]=React.useState(props.model.dimmer);
    const [dimmerShow, setDimmerShow]=React.useState(props.model.dimmerShow);
    const [blinkTimer, setBlinkTimer]=React.useState(props.model.blinkTimer);
    const [blinkSent, setBlinkSent]=React.useState(props.model.blinkSent);
    const [blinkOptions, setBlinkOptions]=React.useState(props.model.blinkOptions);

    React.useEffect( function() {
        function obs() {
            setLightStatus(props.model.lightOn);
            setDimmer(props.model.dimmer);
            setDimmerShow(props.model.dimmerShow);
            setPendingMessage(props.model.pendingMessage);
            setBlinkTimer(props.model.blinkTimer);
            setBlinkSent(props.model.blinkSent);
            setBlinkOptions(props.model.blinkOptions);
        }

        props.model.addObserver(obs);

        return function() {
            props.model.removeObserver(obs);
        }
    }, [props.model]
    )

    return (
        <React.Fragment>
            <ControlsView
                lightStatus = {lightStatus}
                setLight = {x => props.model.setLight(x)}
                setPendingMessage = {(b) => props.model.setPendingMessage(b)}
                pendingMessage = {pendingMessage}
                morseText = {currentMorseText}
                onMorseText = {text => setCurrentMorseText(text)}
                setMorse = {()=> props.model.setMorse(currentMorseText)}
                dimmer = {dimmer}
                dimmerShow = {dimmerShow}
                onMoveDimmer = {value => props.model.setDimmer(value)}
                setBlinkTimer = {value => props.model.setBlinkTimer(value)}
                blinkOptions = {blinkOptions}
            />
        </React.Fragment>
    )
}