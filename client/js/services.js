/// @file services.js
/// @brief AngularJS services, AJAX communication with the server

angular.module('myAppServices', [])
    .service('srvInfo', //current information from zsm server
        function($http) {
            this.baseURL = client_server_prefix + '/ajax/'; //the prefix defined in version.js

            this.getVersion = function(callback) {
                return $http.get(this.baseURL + 'version/get').then(callback);
            };
            this.getCurrent = function(callback) {
                return $http.get(this.baseURL + 'current/get').then(callback);
            };
            this.getCppNumber = function(callback) {
                return $http.get(this.baseURL + 'calcpy/getNumber').then(callback);
            };
        })
    .service('srvCommands', //commands
        function($http) {
            this.baseURL = client_server_prefix + '/ajax/calcpy/'; //the prefix is defined in version.js

            this.getCppCommands = function(callback) {
                return $http.get(this.baseURL + 'getCommands').then(callback);
            };
            this.startCommand = function(callback) {
                return $http.get(this.baseURL + 'startCommand').then(callback);
            };
        })
    .service('gameCommands', //commands
        function($http) {
            this.baseURL = client_server_prefix + '/ajax/game/'; //the prefix is defined in version.js

            this.startGame = function(callback) {
                return $http.get(this.baseURL + 'startGame').then(callback);
            };
            this.handleMove = function(callback) {
                return $http.get(this.baseURL + 'handleMove').then(callback);
            };
            this.validateMove = function(callback) {
                return $http.get(this.baseURL + 'validateMove').then(callback);
            };
            this.isGameFinished = function(callback) {
                return $http.get(this.baseURL + 'isGameFinished').then(callback);
            };
            this.isGameStarted = function(callback) {
                return $http.get(this.baseURL + 'isGameStarted').then(callback);
            }
            this.getBoard = function(callback) {
                return $http.get(this.baseURL + 'getBoard').then(callback);
            }
        });