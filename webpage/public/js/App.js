function App(props){

    return  (
            <div className="">
                <Show hash="#home"><HomePresenter model = { props.model } /></Show>
                <Show hash="#about"><AboutPresenter model = { props.model } /></Show>
                <Show hash="#controls"><ControlsPresenter model = { props.model } /></Show>
                <Show hash="#login"><LoginPresenter model = { props.model } /></Show>
            </div>
    );
}

function defaultRoute(){
    if(!["#home", "#login", "#about", "#controls"].find((knownRoute)=> knownRoute === window.location.hash))
        window.location.hash="#home";
}
defaultRoute(); // when the application loads, set the default route!
window.addEventListener("hashchange", defaultRoute);