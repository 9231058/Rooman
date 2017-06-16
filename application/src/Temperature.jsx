import React from 'react';
import axios from 'axios';


class Temperature extends React.Component {
  constructor() {
    super();
    this.state = {temprature: 0};
  }

  fetch() {
    axios.get('/t.json')
      .then(res => {
        const temperature = res.data.temperature;
        this.setState({temperature});
      });
  }
}

export default Temperature;
