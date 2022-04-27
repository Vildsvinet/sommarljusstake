function LoginView(props) {
    return <div>

        <input type="text" placeholder="E-mail" onInput = { event => props.onEmailText(event.target.value) } required/>
        <br/>
        <input type="password" placeholder="Password" onInput = { event => props.onPasswordText(event.target.value) } required/>
        <br/>
        <button className="" onClick={() => {props.loginCurrentUser()} } type="submit">Login</button>
    </div>


}