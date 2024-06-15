import { useEffect, useState } from "react";
import IGameProps from "./IGameProps";
import Player from "./Player";
import Timer from "./Timer";
import logo from '../resources/running-robot-game-logo.png';
import startScreenImg from '../resources/start-screen-image.jpg';
import {MdSettings, MdGamepad} from "react-icons/md";
import settingsGear from '../resources/settings-icon.png';
import wolf from '../resources/wolf.jpg';
import wolf2 from '../resources/wolf2.jpg';



enum ComponentStates {
    ActiveGame,
    StartScreen,
    ResultsScreen,
    OptionsScreen,
    ControlsScreen,
}

const Game = (props: IGameProps): JSX.Element => {
    const [componentState, setComponentState] = useState<ComponentStates>(ComponentStates.StartScreen);
    const [players, setPlayers] = useState<Player[]>([]);
    const [count, setCount] = useState(1);
    // const [activeGame, setActiveGame] = useState(false);

    switch(componentState) {
        default:
        case ComponentStates.StartScreen:
            return (
                <div className="App">
                    <MdSettings onClick={()=>setComponentState(ComponentStates.OptionsScreen)} className='option-button'></MdSettings>
                    <MdGamepad onClick={()=>setComponentState(ComponentStates.ControlsScreen)} className='controls-button'></MdGamepad>
                    <img src={startScreenImg} alt="arnieFace"  className="start-screen-banner"></img>
                    <img src={logo} alt="logo" className='logo-start-screen'></img>
                    <button onClick={()=>setComponentState(ComponentStates.ActiveGame)} className='start-game-button'>Start</button>
                </div>
            );
        case ComponentStates.ActiveGame:
            return (
                <div className="App">
                    <MdSettings onClick={()=>setComponentState(ComponentStates.OptionsScreen)} className='option-button'></MdSettings>
                    <MdGamepad onClick={()=>setComponentState(ComponentStates.ControlsScreen)} className='controls-button'></MdGamepad>
                    <img src={logo} alt="logo" className='logo-game-screen'></img>
                    <Timer/>
                    <button onClick={() => setComponentState(ComponentStates.StartScreen)} className="quit_button">Quit</button>
                    <button onClick={updatePlayersList}>Add New Player</button>
                    <button onClick={() => console.log(players)}>Log to Console</button>
                    {players.map(player => {
                        return (
                            <div key={player.name} className="Player">
                                <h2>{player.name}</h2>
                                <h3>Score: {player.score}</h3>
                                <h3>Hits Taken: {player.hitsTaken}</h3>
                                <h3>Shots Fired: {player.shotsFired}</h3>
                                <h3>Shots Hit: {player.successfulShots}</h3>
                                <h3>Accuracy: {player.accuracy}</h3>
                                <br></br>
                                <br></br>
                            </div>
                        );
                    })}
                </div>
            );
        case ComponentStates.OptionsScreen:
            return (
                <div className="App">
                    <button onClick={() => setComponentState(ComponentStates.StartScreen)} className="quit_button">Back</button>
                    <img src={wolf} alt="wolf" className="wolf-lol"></img>
                </div>
            );
        case ComponentStates.ControlsScreen:
            return (
                <div className="App">
                    <button onClick={() => setComponentState(ComponentStates.StartScreen)} className="quit_button">Back</button>
                    <img src={wolf2} alt="wolf2" className="wolf-lol"></img>
                </div>
            );
    }

    // return (
    //     <div className="App">
    //         <Timer/>
    //         <button onClick={updatePlayersList}>Add New Player</button>
    //         <button onClick={() => console.log(players)}>Log to Console</button>
    //         {players.map(player => {
    //             return (
    //                 <div key={player.name} className="Player">
    //                     <h2>{player.name}</h2>
    //                     <h3>Score: {player.score}</h3>
    //                     <h3>Hits Taken: {player.hitsTaken}</h3>
    //                     <h3>Shots Fired: {player.shotsFired}</h3>
    //                     <h3>Shots Hit: {player.successfulShots}</h3>
    //                     <h3>Accuracy: {player.accuracy}</h3>
    //                     <br></br>
    //                     <br></br>
    //                 </div>
    //             );
    //         })}
    //     </div>
    // );

    function updatePlayersList () {
        let newPlayer = new Player('Player ' + count);
        setPlayers(players => [...players,newPlayer]);
        setCount(count => count + 1);
    }

}

export default Game;