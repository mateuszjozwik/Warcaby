/// @file controllers.js
/// @brief AngularJS controllers

angular.module('myAppControllers', [])
	.controller('gameController', function ($scope, gameCommands) {

		$scope.colors = {
			0: 'Black',
			1: 'White'
		};

		$scope.boardData = null;
		$scope.gameResult = 'pending';
		$scope.data  = {
			'isGameStarted': false,
            'isGameFinished': false
		};
		$scope.initView = function() {
			$scope.gameState = 'WAITING_FOR_USER';

			$scope.getBoard();
		};

		$scope.getBoard = function() {
			gameCommands.getBoard(
				function (data) {
                    $scope.boardData = data.data.board;
                    console.log($scope.boardData);
                    $scope.updateBoard();
                }
			)
		};

		// todo: hardcoded data for visual purpose
		$scope.gameStats = {
			computer: {
				wins: 2,
				loses: 4,
				leftPounds: 7,
				takenPounds: 9,
			},
            player: {
                wins: 13,
                loses: 2,
                leftPounds: 15,
                takenPounds: 1,
            },
		};
		$scope.startGame = function() {
            gameCommands.startGame(
                function (data) {
                    if (data.status === 200) {
                        $scope.data.isGameStarted = data.data.isGameStarted;
                        $scope.gameState = 'STARTED';
					}
                }
            );
		};
        $scope.isGameFinished = function () {
            gameCommands.isGameFinished(
                function (data) {
                    $scope.data.isGameFinished = data.data.isGameFinished;
                }
            );
        };

        $scope.isGameStarted = function () {
            gameCommands.isGameStarted(
                function (data) {
                    $scope.data.isGameStarted = data.data.isGameStarted;
                }
            );
        };

        //todo fetch width and height from backend
        $scope.updateBoard = function() {
            let width = 8;
            let height = 8;
            $scope.board = new Array(width);
            for (let x = 0; x < width; ++x) {
                $scope.board[x] = new Array(height);
                for (let y= 0; y < height; ++y) {

                    let cell = {
                        x: $scope.boardData[x][y].position.x,
                        y: $scope.boardData[x][y].position.y,
                        even: ((x + y) % 2) == 0,
                        'hasPawn': $scope.boardData[x][y].hasPawn,
                        'isGameField': $scope.boardData[x][y].isGameField,

                    };

					if ($scope.boardData[x][y].hasPawn) {
						cell.pawn = {};
                        cell.pawn.isAlive = $scope.boardData[x][y].pawn.isAlive;
                        cell.pawn.isQueen = $scope.boardData[x][y].pawn.isQueen;
                        cell.pawn.color = $scope.boardData[x][y].pawn.color;
                        cell.pawn.chosen = false;
                    }

                    $scope.board[x][y] = cell;
                }
            }
        };

        $scope.isChosen = function(field) {
            if (field.hasPawn) {
                return field.pawn.chosen;
            }
		};

        $scope.choose = function(field) {
        	if (field.hasPawn) {
        		$scope.unChooseFields();
                field.pawn.chosen = true;
            }
		};

        $scope.unChooseFields = function() {
            for (let x = 0; x < 8; ++x) {
                for (let y = 0; y < 8; ++y) {
                	if (angular.isDefined($scope.board[x][y].pawn)) {
                        $scope.board[x][y].pawn.chosen = false;
                    }
                }
            }
		}

        $scope.getFieldImage = function(field) {
        	var prefix = '/images';
        	var sufix = '.png'
        	if (!field.hasPawn) {
        		return $scope.getUrl('/field') ;
			} else if (field.hasPawn) {
        		return $scope.getUrl('/pawn' + $scope.colors[field.pawn.color]);
			}
		};

		$scope.getUrl = function(type) {
        	return '/images' + type + '.png';
		};

        $scope.initView();
    })
	.controller('historyController', function ($scope) {

    })
    .controller('settingsController', //client static settings
        ['$scope',
            '$translate',
            function($scope, $translate) {
                $scope.langs = ['en', 'pl'];
                $scope.changeLanguage = function (lang) {
                    $translate.use(lang);
                };
            }])
	.controller('versionController', //versions of system modules
				['$scope',
				 'srvInfo',
				 function($scope, srvInfo) {
					 srvInfo.getVersion(
					 	 function(data) {
					 		 $scope.server_ver = data;
					 	 });
					 srvInfo.getCppNumber(
						 function(data) {
							 $scope.cpp_get = data;
						 });
					 $scope.client_ver = client_ver_major.toString() + '.' + client_ver_minor.toString() + '.' + client_ver_compilation.toString(); //from version.js file
				 }])
	.controller('commandController', //cpp commands
				['$scope',
				 'srvCommands',
				 function($scope, srvCommands) {
					 $scope.getCppCommandsNo = function() {
						 srvCommands.getCppCommands(
							 function(data) {
								 $scope.cpp_commands_no = Object.keys(data).length;
							 });
					 };
					 $scope.clickNewCommand = function() {
						 srvCommands.startCommand(
							 function(data) {
								 $scope.getCppCommandsNo();
							 })
					 };
					 $scope.getCppCommandsNo();
				 }])
	.controller('currentController', //current server params
				['$scope',
				 '$timeout',
				 'srvInfo',
				 'srvCommands',
				 function($scope, $timeout, srvInfo, srvCommands) {
					 var REFRESH_INTERVAL = 1000; //ms

					 var call = function() { //function called periodically
						 $scope.getCppCommands = function() {
							 srvCommands.getCppCommands(
								 function(data) {
									 $scope.cpp_commands = data;
								 });
						 };

						 srvInfo.getCurrent(
					 		 function(data) {
					 			 $scope.current = data;
								 $scope.getCppCommands();
								 $timeout(call, REFRESH_INTERVAL);
					 		 });
					 };
					 $timeout(call, 0); //start calling the service
				 }]);

