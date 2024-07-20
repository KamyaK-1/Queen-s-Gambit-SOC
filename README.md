# Queen-s-Gambit-SOC
Contains the weekly assignments given during the SOC Project-Queen's Gambit.
After Week3, our only task was to make an engine.


You can play against my engine by running the executable engine
```console
./engine/engine
```
If you want a different starting position, do the following changes:



i) Inside the main function of engine.cpp, change the value of fen_str to the FEN of starting position you want. Go to [Chess.com](https://www.chess.com/analysis) and set up the position. Click on share button and you get the FEN notation of your desired position.


ii) Call the constructor of board with "fen_str"

  string fen_str = "FEN_POSITION_OF_YOUR_WISH";
  
  chess::Board board = Board(fen_str);
