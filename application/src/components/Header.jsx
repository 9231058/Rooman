import React from 'react'

class Header extends React.Component {
  render () {
    return (
      <nav className='navbar navbar-toggleable-md navbar-light bg-faded mb-2'>
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
    )
  }
}

export default Header
