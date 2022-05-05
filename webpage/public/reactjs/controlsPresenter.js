function ControlsPresenter(props){
    const [lightStatus, setLightStatus]=React.useState(props.model.lightOn);
    const [currentMorseText, setCurrentMorseText] = React.useState(props.model.morseText);
    const [dimmer, setDimmer]=React.useState(props.model.dimmer);

    React.useEffect( function() {
        function obs() {
            setLightStatus(props.model.lightOn);
            setDimmer(props.model.dimmer);

        }

        props.model.addObserver(obs);

        return function() {
            props.model.removeObserver(obs);
        }
    }, [props.model])

    return (
        <React.Fragment>
            <ControlsView
                lightStatus = {lightStatus}
                setLight = {x => props.model.setLight(x)}
                morseText = {currentMorseText}
                onMorseText = {text => setCurrentMorseText(text)}
                setMorse = {()=> props.model.setMorse(currentMorseText)}
                dimmer = {dimmer}
                onMoveDimmer = {value => props.model.setDimmer(value)}

            />
        </React.Fragment>
    )
}