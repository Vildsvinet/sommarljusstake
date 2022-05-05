function AboutView(props) {
    return (
        <div>
            <center>
                <h1>The team behind Sommarljusstake</h1>
                <p>
                <img src={"team1.jpg"} width={"500px"} alt={"The team"}/><br/>

                Project Manager: Jonathan <br/>
                Stakeholder Representative: Kristian<br/>
                System Architect: Tove <br/>
                Lead Developer: Linux <br/>
                Test Leader: Niclas <br/>
                Sustainability and Work Environment Officer: Malin <br/>
                </p>

                <h1>Our Product</h1>
                <p>
                    The Sommarljusstake offers a mood boost for your rainy Midsummer party.
                    With our product you can never go wrong - guaranteed dancing and automatic
                    reminders to buy more Nubbe if needed.
                </p>

                <p>
                <button onClick={() => window.location.hash = "#home"}>
                    back to home
                </button><br/>
                <button onClick={() => window.location.href = "mailto:info@sommarljusstake.se"}>
                    contact
                </button>
                </p>
            </center>
        </div>
    )
}