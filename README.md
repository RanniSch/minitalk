# minitalk
The purpose of this project is a small data exchange program using UNIX signals. It is a communication program in the form of a client and a server. <br>
The server is able to receive strings from several clients in a row without needing to restart.<br>
Only these two signals are used: SIGUSR1 and SIGUSR2<br><br>

## How to run minitalk
* In your terminal run: ```make```
* Start the server with ```.\server```
* Open a second terminal and start the client with ```.\client```

![minitalk-01](https://github.com/RanniSch/minitalk/assets/104382315/852bf3b7-2285-43a5-ad53-bf70027f4c84)
