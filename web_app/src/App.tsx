import React from 'react';
// import logo from './logo.svg';
import logo from './resources/running-robot-game-logo.png';
import wolf from './resources/wolf.jpg';
import './App.css';
import Game from './components/Game';
import {MdSettings} from "react-icons/md";

function App() {
  return (
    <div className="App">
      {/* <MdSettings onClick={displaySettings} className='option-button'></MdSettings> */}
      <Game game_id={0}/>
    </div>
  );
}

function displaySettings() {
  return (
    <img src={wolf} alt="wolf"></img>
  )
}

export default App;
