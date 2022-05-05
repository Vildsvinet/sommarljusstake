function HomePresenter(props){
    const [lightStatus, setLightStatus]=React.useState(props.model.lightOn);
    const [currentUser, setCurrentUser] = React.useState(props.model.currentUser);

    React.useEffect( function() {
        function obs() {
            setLightStatus(props.model.lightOn); setCurrentUser(props.model.currentUser);
        }

        props.model.addObserver(obs);

        return function() {
            props.model.removeObserver(obs);
        }
    }, [props.model])

    return <React.Fragment>
        <HomeView
            lightStatus = {lightStatus}
            setLight = {x => props.model.setLight(x)}
            currentUser = {currentUser}
            signOut = {() => props.model.signOut()}
            // morseText = {props.model.morseText}
        />
    </React.Fragment>

}