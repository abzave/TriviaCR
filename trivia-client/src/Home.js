import logo from "./assets/logo.gif";
import "./Home.scss";
import React from "react";

class Home extends React.Component {
  constructor(props) {
    super(props);
    this.state = { value: "" };

    this.handleChange = this.handleChange.bind(this);
    this.handleSubmit = this.handleSubmit.bind(this);
  }

  handleChange(event) {
    this.setState({ value: event.target.value });
  }

  handleSubmit(event) {
    alert("A name was submitted: " + this.state.value);
    event.preventDefault();
  }

  render() {
    return (
      <div className="HomeContainer">
        <img src={logo} className="Logo" alt="logo" />
        <h3 className="HomeHeading">Ingresa tu nombre de usuario</h3>
        <form className="LoginForm" onSubmit={this.handleSubmit}>
          <input
              className="UsernameInput"
              type="text"
              value={this.state.value}
              onChange={this.handleChange}
            />
          <input className="FormButton" type="submit" value="Ingresar" />
        </form>
      </div>
    );
  }
}

function handleChange(event) {
  this.setState({ value: event.target.value });
}

function handleSubmit(event) {
  alert("A name was submitted: " + this.state.value);
  event.preventDefault();
}

export default Home;
