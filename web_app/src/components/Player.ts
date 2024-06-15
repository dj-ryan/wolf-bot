export default class Player {
    _name: string;
    _hitsTaken: number;
    _score: number;
    _accuracy: number;
    _shotsFired: number;
    _successfulShots: number;

    constructor(name: string) {
        this._name = name;
        this._accuracy = 0;
        this._hitsTaken = 0;
        this._score = 0;
        this._shotsFired = 0;
        this._successfulShots = 0;
    }
    set name(name: string) {
        this._name = name;
    }
    set hitsTaken(hitsTaken: number) {
        this._hitsTaken = hitsTaken;
    }
    set score(score: number) {
        this._score = score;
    }
    set accuracy(accuracy: number) {
        this._accuracy = accuracy;
    }
    set shotsFired(shotsFired: number) {
        this._shotsFired = shotsFired;
    }
    set successfulShots(successfulShots: number) {
        this._successfulShots = successfulShots;
    }
    get name() {
        return this._name;
    }
    get hitsTaken() {
        return this._hitsTaken;
    }
    get score() {
        return this._score;
    }
    get accuracy() {
        return this._accuracy;
    }
    get shotsFired() {
        return this._shotsFired;
    }
    get successfulShots() {
        return this._successfulShots;
    }
}