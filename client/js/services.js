/// @file services.js
/// @brief AngularJS services, AJAX communication with the server

angular.module('myAppServices', [])
    .service('gameCommands', //commands
        function($http) {
            this.baseURL = client_server_prefix + '/ajax/game/'; //the prefix is defined in version.js

            this.startGame = function(callback) {
                return $http.get(this.baseURL + 'startGame').then(callback);
            };
            this.handleMove = function(pawnField, destinationField, canPawnKill, callback) {
                return $http.get(this.baseURL + 'handleMove', {
                    params: {
                        pawnX: pawnField.x,
                        pawnY: pawnField.y,
                        destinationX: destinationField.x,
                        destinationY: destinationField.y,
                        canPawnKill: canPawnKill ? 1 : 0
                    }
                }).then(callback);
            };

            this.canMove = function(pawnField, callback) {
                return $http.get(this.baseURL + 'canMove', {
                    params: {
                        pawnFieldX: pawnField.x,
                        pawnFieldY: pawnField.y,
                    }
                }).then(callback);
            };

            this.restartGame = function(callback) {
                return $http.get(this.baseURL + 'restartGame').then(callback);
            };
            this.validateMove = function(callback) {
                return $http.get(this.baseURL + 'validateMove').then(callback);
            };
            this.isGameFinished = function(callback) {
                return $http.get(this.baseURL + 'isGameFinished').then(callback);
            };
            this.isGameStarted = function(callback) {
                return $http.get(this.baseURL + 'isGameStarted').then(callback);
            };
            this.getBoard = function(callback) {
                return $http.get(this.baseURL + 'getBoard').then(callback);
            }
        });