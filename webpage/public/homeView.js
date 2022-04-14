function HomeView(props) {
    return (
        <div>
            <center>
                <button>
                    press this button to turn on the Sommarljusstake
                </button>
            </center>
            <br/>

            <center>
                <button onClick={() => window.location.hash = "#about"}>
                    press this button to read about the team
                </button>
            </center>
        </div>
    )
}
