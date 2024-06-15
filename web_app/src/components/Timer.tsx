import React, { useState, useEffect } from 'react';

const GAMETIME = 30;

const Timer = () => {
    const [isActive, setIsActive] = useState(false);
    const [seconds, setSeconds] = useState(GAMETIME);
    useEffect(() => {
      let timer: any = null;
      if(isActive){
        timer = setInterval(() => {
          setSeconds((seconds) => seconds - 1);
        }, 1000);
        if(seconds === 0) {
            setIsActive(false);
        }
      }
      return () => {
        clearInterval(timer);
      };
    });
    return (
      <div  className="timer">
        <h3>Time Remaining: {seconds}</h3>
        <button className='start-button-timer' onClick={()=>{
          setIsActive(true);
        }}> Start </button>
        <button className='start-button-timer' onClick={()=>{
            setIsActive(false);
            setSeconds(GAMETIME);
        }}> Reset </button>
      </div>
    );
  };

  export default Timer;