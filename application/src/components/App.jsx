import React from 'react'
import Temperature from './Temperature.jsx'
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
          <div className='col-6'>
            <Temperature />
          </div>
        </div>
      </div>
    )
  }
}

export default App
