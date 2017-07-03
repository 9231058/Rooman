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
    }, 5000)
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
          colorPlate='rgba(205,183,158,1)'
          colorBarProgress='rgb(255,106,106)'
          colorTitle='rgb(255,255,255)'
          colorUnits='rgb(255,255,255)'
          colorValueText='rgb(255,255,255)'
          colorNumbers='rgb(255,255,255)'
          minValue={10}
          maxValue={50}
          majorTicks={['10', '15', '20', '25', '30', '35', '40', '45', '50']}
          highlights={[
            { from: 10, to: 25, color: 'rgba(0,255,0,.15)' },
            { from: 25, to: 35, color: 'rgba(255,255,0,.15)' },
            { from: 35, to: 50, color: 'rgba(255,30,0,.25)' }
          ]}
          title='Temperature'
          units='°C'
          value={this.state.temperature}
          valueBox
          valueInt={2}
          valueDec={2}
        />
      </div>
    )
  }
}

export default Temperature
