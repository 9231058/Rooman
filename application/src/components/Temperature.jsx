import React from 'react'
import axios from 'axios'

import {LinearGauge} from 'react-canvas-gauges'

class Temperature extends React.Component {
  constructor (props) {
    super(props)
    this.state = {temprature: 0}
  }

  componentDidMount () {
    setInterval(() => {
      this.fetchTemperature()
    }, 1000)
  }

  fetchTemperature () {
    axios.get('/t')
      .then(res => {
        const t = res.data.temperature
        this.setState({temperature: t})
      })
  }

  render () {
    return (
      <div>
        <LinearGauge
          colorPlate='rgba(255,0,0,0)'
          title='Temperature'
          units='°C'
          value={this.state.temperature}
          valueBox
        />
      </div>
    )
  }
}

export default Temperature
