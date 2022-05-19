function AboutPresenter(props) {

    React.useEffect(function () {
        function obs() {
        }
        //props.model.addObserver(obs);
        return function () {
            //props.model.removeObserver(obs);
        }
    }, [props.model])

    return (
        <React.Fragment>
            <AboutView/>
        </React.Fragment>
    )
}