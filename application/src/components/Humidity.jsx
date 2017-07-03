import React from 'react'
import axios from 'axios'

import {RadialGauge} from 'react-canvas-gauges'

class Humidity extends React.Component {
  constructor (props) {
    super(props)
    this.state = {humidity: 0}
  }

  componentDidMount () {
    setInterval(() => {
      this.fetchHumidity()
    }, 5000)
  }

  fetchHumidity () {
    axios.get('/h')
      .then(res => {
        const h = res.data.humidity
        this.setState({humidity: h})
      })
  }

  render () {
    return (
      <div>
        <RadialGauge
          minValue={0}
          maxValue={100}
          majorTicks={['0', '10', '20', '30', '40', '50', '60', '70', '80', '90', '100']}
          minorTicks={6}
          title='Humidity'
          units='%'
          value={this.state.humidity}
        />
      </div>
    )
  }
}

export default Humidity
