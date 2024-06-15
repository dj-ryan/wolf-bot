import requests

BASE_URL = r"http://127.0.0.1:8000"

if __name__ == "__main__":
    # NOTE: To run this code, first use the command `uvicorn bfcm:app --reload`
    # in api\source to start the local API server
    """
    This test does the following
        1. Creates a game
        2. Populates the game with 2 robots
        3. Has the first robot shoot the second robot
        4. Prints the status of the game
    """
    game_id = requests.put(BASE_URL + "/game/create").text

    NUM_ROBOTS = 2
    for _ in range(NUM_ROBOTS):
        defender_id = requests.put(BASE_URL + f"/join/{game_id}").text

    requests.put(
        BASE_URL +
        f"/hit/{game_id}?attacker_id={int(defender_id) - 1}&defender_id={int(defender_id)}"
    )

    game_status = requests.get(BASE_URL + f"/game/status/{game_id}")
    print(game_status.text)
    results = requests.put(BASE_URL + f"/game/end/{game_id}")
    print(results.text)
