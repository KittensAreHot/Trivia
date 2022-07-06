#pragma once
enum class Prefix {
	LOGINRESPONSE = 101,			//Response to user login
	SIGNUPRESPONSE = 102,			//Response to user signup
	ERRORRESPONSE = 103,			//Error message
	SIGNOUTRESPONSE = 104,			//Response to user signout
	GETROOMSRESPONSE = 105,			//Finding all existing rooms
	GETPLAYERSINROOMRESPONSE = 106,	//Get all the players in a room
	GETPERSONALSTATSRESPONSE = 107,	//Get all statistics about user
	GETHIGHSCORERESPONSE = 108,		//Get best overall statistics saved
	JOINROOMRESPONSE = 109,			//Tries to get the user into the room
	CREATEROOMRESPONSE = 110,		//Tries to create the requested room
	CLOSEROOMRESPONSE = 111,		//Closes the room as an admin
	STARTGAMERESPONSE = 112,		//Starts the room as an admin
	GETROOMSTATERESPONSE = 113,		//Gets the data about the specified room
	LEAVEROOMRESPONSE = 114,		//Removes the user from the room
	LOGINREQUEST = 51,				//User's request to login
	SIGNUPREQUEST = 52,				//User's request to signup
	SIGNOUTREQUEST = 53,			//User's request to signout
	GETROOMSREQUEST = 54,			//User's request to get all rooms
	GETPLAYERSINROOMREQUEST = 55,	//User's request to get all the players in a certain room
	GETPERSONALSTATSREQUEST = 56,	//User's request to get all the statistics about himself
	GETHIGHSCOREREQUEST = 57,		//User's request to get best known statistics
	JOINROOMREQUEST = 58,			//User's request to join a room
	CREATEROOMREQUEST = 59,			//User's request to create a room
	CLOSEROOMREQUEST = 60,			//User's request to leave and delete a room
	STARTGAMEREQUEST = 61,			//User's request to start the room he is in
	GETROOMSTATEREQUEST = 62,		//User's request to recieve the data about the room
	LEAVEROOMREQUEST = 63,			//User's request to leave a room
};