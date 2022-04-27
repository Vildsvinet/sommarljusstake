function LoginPresenter(props){
    const [currentEmail, setCurrentEmail] = React.useState(props.model.email);
    const [currentPassword, setCurrentPassword] = React.useState(props.model.password);

    React.useEffect( function() {
        function currentObserver() {
            setCurrentEmail(props.model.email);
            setCurrentPassword(props.model.password);
        }
            
        props.model.addObserver(currentObserver);

        return function() {
            props.model.removeObserver(currentObserver);
        }
    }, [props.model])

    return <React.Fragment>
        <LoginView
            email = {currentEmail}
            password = {currentPassword}
            onEmailText = {text => setCurrentEmail(text)}
            onPasswordText = {text => setCurrentPassword(text)}
            loginCurrentUser = {() => props.model.signInEmail(currentEmail, currentPassword)}
        />
        </React.Fragment>
}