
/*set the default user view to the game view*/
function defaultRoute(){
    if(!routeKnownQ()) window.location.hash="#home";

    window.addEventListener(
        "hashchange", defaultRoute);
}

/*Check whether subpage is known, i e one of our views*/
function routeKnownQ(){
    return(
        ["#home", "#about"]           //add all hashes here
            .find((knownRoute)=>{
                return(knownRoute === window.location.hash)})
    )
}

function App(props){
    defaultRoute(); // when the application loads, set the default route

    const [hashState, setHash] = React.useState(window.location.hash);

    React.useEffect(function () {
            const listener = function () {
                setHash(window.location.hash);
            }
            window.addEventListener("hashchange", listener);   // 1 subscribe

            return function () {
                window.removeEventListener("hashchange", listener)
            } // 2 unsubsribe
        }, []
    );

    if (window.location.hash ==="#home") return <div><HomeView/></div>
    if (window.location.hash ==="#about") return <div><AboutView/></div>

    return <div>unexpected page</div>
}