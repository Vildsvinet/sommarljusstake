function LoginView(props) {
    return <div>
        <br/>
        <form>
        <input type="text" placeholder="E-mail" onInput={event => props.onEmailText(event.target.value)} required/>
        <br/>
        <input type="password" placeholder="Password" onInput={event => props.onPasswordText(event.target.value)}
               required/>
        </form>
            <br/>
        <button className="" onClick={() => {
            props.loginCurrentUser()
        }} type="submit">Sign In</button>
        <br/>
        <button onClick={() => window.location.hash = "#home"}>Back to Home</button>
    </div>
}