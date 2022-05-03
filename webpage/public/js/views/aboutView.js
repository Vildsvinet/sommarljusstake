function AboutView(props) {
    return (
        <div>
            <center>
                <img src={"team1.jpg"} width={"300px"} alt={"The team"}/><br/>
                The team behind Sommarljusstake<br/>

                <button onClick={() => window.location.hash = "#home"}>
                    back to home
                </button>
            </center>
        </div>
    )
}