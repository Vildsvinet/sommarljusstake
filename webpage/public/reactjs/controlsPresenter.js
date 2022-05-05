function ControlsPresenter(props){
    const [lightStatus, setLightStatus]=React.useState(props.model.lightOn);
    const [currentMorseText, setCurrentMorseText] = React.useState(props.model.morseText);

    React.useEffect( function() {
        function obs() {
            setLightStatus(props.model.lightOn);

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

            />
        </React.Fragment>
    )
}