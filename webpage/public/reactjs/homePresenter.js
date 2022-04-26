function HomePresenter(props){

    React.useEffect( function() {
        function obs() {

        }
        
        //props.model.addObserver(obs);
                                      
        return function() {
            //props.model.removeObserver(obs);
        }                               
    }, [props.model])                      

    return (
            <React.Fragment>
                <HomeView
                />
            </React.Fragment>
    )
}