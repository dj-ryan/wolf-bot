# TODO: Hook this up to a database after the initial prototype

import os
import dataclasses
from datetime import datetime

from fastapi import FastAPI, APIRouter
import fastapi.middleware.cors as cors
import pandas as pd

openapi_prefix = ""

app = FastAPI()

router = APIRouter(prefix=openapi_prefix)


origins = ['*']

app.add_middleware(
    cors.CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

current_id = 0

games = dict()


@dataclasses.dataclass
class Robot:
    robot_id: int
    score: int = 0
    shots: int = 0
    hits: int = 0

    def get_accuracy(self) -> float:
        """Calculates the accuracy of the robot.

        Returns:
            float: The percent of the shots that hit when fired.
        """
        return float(self.hits) / float(self.shots)


@dataclasses.dataclass
class Game:
    game_id: int
    start_time: pd.Timestamp
    active: bool = True
    robots: dict = None


@router.put("/join/{game_id}")
def join_game(game_id: int) -> int:
    """Registers the robot and returns a unique number that is used to
    identify the robot to a specific game.

    Args:
        game_id (int):
            The game that the robot should be registered to.

    Returns:
        int: The identification number for the robot. If the game is not valid,
        then this returns -1
    """
    # TODO: Retreive the next available ID from the database
    global current_id
    current_id += 1
    robot = Robot(robot_id=current_id)
    game = games.get(
        game_id,
        Game(game_id=-1, start_time=datetime.now().timestamp()),
    )
    if game.game_id == -1:
        return -1
    if not game.active:
        return -1
    if game.robots is None:
        game.robots = dict()
    game.robots[current_id] = robot
    games[game_id] = game

    return current_id


@router.put("/hit/{game_id}")
def register_hit(game_id: int, attacker_id: int, defender_id: int) -> int:
    """Receives the identification number of both the emitter and the receiver
    for a laser tag hit and does the following.
    1. Ensures that both the attacker and defender ID are valid
    2. Ensures that the attacker and defender are on separate teams
    3. Awards points to the attacker if the hit is valid
    4. Returns a response to the defender on whether it has been hit or not

    Args:
        game_id (int):
            The identification number of the game that the robots are in
        attacker (int): 
            The identification number of the robot that attacked
        defender (int): 
            The identification number of the robot that received the hit

    Returns:
        int: Returns 1 if the hit is not friendly fire, otherwise returns 0
    """
    # If the robots are on different teams, send back the hit signal
    game = games.get(
        game_id,
        Game(game_id=-1, start_time=datetime.now().timestamp()),
    )
    if game.game_id == -1:
        return 0
    # TODO: Add a way to hold teams until the database is implemented
    # Handle adding points
    attacker = game.robots.get(attacker_id, Robot(robot_id=-1))
    if attacker.robot_id == -1:
        return 0
    attacker.score += 500
    attacker.hits += 1
    game.robots[attacker_id] = attacker
    games[game_id] = game
    return 1


@router.get("/game/status/{game_id}")
def game_status(game_id: int, robot_id: int = -1) -> dict:
    """Returns all of the information about the current game, or
    information about a specific robot if requested..

    Args:
        game_id (int): 
            The identification number of the targeted game.
        robot_id (int):
            The identification number of the robot if information about
            a specific robot is required. If this is set to -1, then
            information about all of the robots in the game is returned.
            (Optional) Defaults to: -1

    Returns:
        dict: All of the information of the game represented as a dict
    """
    game = games.get(game_id, Game(
        game_id=-1, start_time=datetime.now().timestamp()))
    if game.game_id == -1:
        return None
    if robot_id >= 0:
        pass
    return game.__dict__


@router.put("/game/create")
def create_game() -> int:
    """Creates a game and returns the ID of the game.

    Returns:
        int: The identification number of the game.
    """
    game_id = len(games)
    timestamp = datetime.now().timestamp()
    game = Game(game_id=game_id, start_time=timestamp)
    games[game_id] = game
    return game_id


@router.get("/game")
def retreive_games() -> list:
    """Retreives a list of the games in the system, ordering them from most
    newest game to the oldest game.

    Returns:
        list: Simplified information for each game in the system

        TODO: Make this return less scary information than a list of all
        of the games
    """
    return [game.__dict__ for game in games.values()]


@router.put("/game/end/{game_id}")
def end_game(game_id: int) -> int:
    """Finds the given game and sets it as inactive.

    Args:
        game_id (int): 
            The identification number for the game ending.

    Returns:
        int: 
            Returns 1 if the game ending was successful, otherwise returns 0
    """
    game = games.get(
        game_id,
        Game(-1, datetime.now())
    )
    if game.game_id == -1:
        return 0

    games.pop(game_id)
    return 1


@router.put("/shoot/{game_id}")
def attempt_shot(game_id: int, attacker_id: int) -> int:
    """Sends a message to the server that a shot has been attempted
    by the attacker.

    Args:
        game_id (int): 
            The identification number of the game that the robot is in.
        attacker_id (int): 
            The identification number of the robot.

    Returns:
        int: The number of shots attempted by the attacker, or -1 if the
        robot can not be found.
    """
    game = games.get(
        game_id,
        Game(-1, datetime.now())
    )
    if game.game_id == -1:
        return -1

    robot = game.robots.get(attacker_id, None)
    if robot is None:
        return -1

    robot.shots += 1
    game.robots[attacker_id] = robot
    games[game_id] = game
    return robot.shots


app.include_router(router)
