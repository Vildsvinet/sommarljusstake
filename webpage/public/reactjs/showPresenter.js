function Show(props) {
    const [hashState, setHash]= React.useState(window.location.hash);

    React.useEffect ( function (){
        const listener = function () {setHash(window.location.hash);}
        window.addEventListener("hashchange", listener); // Subscribe
        return function () {window.removeEventListener("hashchange", listener)} // Unsubscribe
    },[]);
    // Gömmer enbart, problematiskt när man vill nyttja mounting.
   /* if (hashState !== props.hash) {
        return <div className="hidden">
            {props.children}
        </div>
    }
    else {
        return <div className="">
            {props.children}
        </div>
    }*/
    // Mountar om, såsom man förväntar sig att det ska fungera!
    return hashState !== props.hash ? "" : props.children;

}