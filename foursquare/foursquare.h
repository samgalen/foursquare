struct Game;
/* say whether game2 is a possible next move of game1 */
bool nextMove(Game game1, Game game2);
/* array of possible next moves */
Game *possMoves(Game *game1);
/* says whether or not two games are the same */
bool equal(Game *game1, Game *game2);
