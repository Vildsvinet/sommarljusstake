function HomePresenter(props){
    const [currentUser, setCurrentUser] = React.useState(props.model.currentUser);

    React.useEffect( function() {
        function obs() {
            setCurrentUser(props.model.currentUser);
        }
        props.model.addObserver(obs);

        return function() {
            props.model.removeObserver(obs);
        }
    }, [props.model])

    return <React.Fragment>
        <HomeView
            currentUser = {currentUser}
            signOut = {() => props.model.signOut()}
        />
    </React.Fragment>
}