function HomePresenter(props){
    const [lightStatus, setLightStatus]=React.useState(props.model.lightOn);

    React.useEffect( function() {
        function obs() {
            setLightStatus(props.model.lightOn)
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
        />
    </React.Fragment>

}