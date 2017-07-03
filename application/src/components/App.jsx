import React from 'react'
import Temperature from './Temperature.jsx'

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
        <nav className='navbar navbar-toggleable-md navbar-light bg-faded'>
          <button className='navbar-toggler navbar-toggler-right' type='button'
            data-toggle='collapse' data-target='#navbar' aria-controls='navbar'
            aria-expanded='false' aria-label='Toggle navigation'>
            <span className='navbar-toggler-icon' />
          </button>
          <a className='navbar-brand' href='/'>Rooman</a>

          <div className='collapse navbar-collapse' id='navbar'>
            <ul className='navbar-nav mr-auto'>
              <li className='nav-item active'>
                <a className='nav-link' href='#'
                  onClick={() => {
                    this.changeLocation('Home')
                  }}>
                  Home <span className='sr-only'>(current)</span>
                </a>
              </li>
            </ul>
          </div>
        </nav>
        <div>
          <Temperature />
        </div>
      </div>
    )
  }
}

export default App
