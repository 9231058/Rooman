import React from 'react';
import axios from 'axios';


class Temperature extends React.Component {
  constructor(props) {
    super(props);
    this.state = {temprature: 0};
  }

  componentDidMount() {
    setInterval(() => {
      this.fetchTemperature();
    }, 1000);
  }

  fetchTemperature() {
    axios.get('/t')
      .then(res => {
        const t = res.data.temperature;
        this.setState({temperature: t});
      });
  }

  render() {
    return (
      <div>
        {this.state.temperature}
      </div>
    );
  }
}

export default Temperature;
