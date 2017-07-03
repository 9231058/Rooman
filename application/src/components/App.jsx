import React from 'react'
import Temperature from './Temperature.jsx'
import Humidity from './Humidity.jsx'
import Header from './Header.jsx'

import 'bootstrap/dist/css/bootstrap.min.css'

class App extends React.Component {
  constructor (props) {
    super(props)
    this.state = {location: 'Home'}
  }

  changeLocation (newLocation) {
    this.setState({
      location: newLocation
    })
  }

  render () {
    return (
      <div>
        <Header />
        <div className='container'>
          <div className='row'>
            <div className='col-6'>
              <Temperature />
            </div>
            <div className='col-6'>
              <Humidity />
            </div>
          </div>
        </div>
      </div>
    )
  }
}

export default App
