function ControlsPresenter(props){
    const [currentMorseText, setCurrentMorseText] = React.useState(props.model.morseText);

    React.useEffect( function() {
        function obs() {

        }

        props.model.addObserver(obs);

        return function() {
            props.model.removeObserver(obs);
        }
    }, [props.model])

    return (
        <React.Fragment>
            <ControlsView
                morseText = {currentMorseText}
                onMorseText = {text => setCurrentMorseText(text)}

            />
        </React.Fragment>
    )
}