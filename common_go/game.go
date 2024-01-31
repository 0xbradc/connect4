/** @file game.go
*
* @brief Connect4 Game Logic in Go
*
* @par   
* COPYRIGHT NOTICE: MIT License
*/

package game

const NUM_ROWS int8 = 6
const NUM_COLS int8 = 7

type GameInformation struct {
	UserName string
	Board int8[NUM_ROWS][NUM_COLS]
}

const (
	TILE_OPEN int8 = 0
	TILE_PLAYER int8 = 1
	TILE_AI int8 = 2
)

func apply_move(game GameInformation, player int8, col int8) bool
{
	if (0 > col || NUM_COLS <= col)
	{
		return false // Column out of range
	}

	if (TILE_PLAYER != player && TILE_AI != player)
	{
		return false // Player not recognized 
	}

	for int i := (NUM_ROWS - 1); i >= 0; --i 
	{
		if game.board[i][col] == TILE_OPEN
		{
			game.board[i][col] = player
			return true
		}
	}
	return false
}

func is_board_full(game GameInformation) bool 
{
	// Assuming the board is under the influence of gravity, 
	// we only need to check the top row
	for i := 0; i < NUM_COLS; ++i 
	{
		if game.board[0][i] == TILE_OPEN
		{
			return false
		}
	}

	return true
}

func is_winner(game GameInformation, player int8) bool 
{
    var dfs = func(r, c, dr, dc, count int) bool 
	{
        if r < 0 || r >= NUM_ROWS || c < 0 || c >= NUM_COLS || board[r][c] != player 
		{
            return false
        }
        if count == 3 
		{
            return true // Indicates four in a row
        }
        return dfs(r + dr, c + dc, dr, dc, count + 1)
    }

    for r := 0; r < NUM_ROWS; ++r 
	{
        for c := 0; c < NUM_COLS; ++c 
		{
            if board[r][c] == player 
			{
                // Check all directions
                if dfs(r, c, 0, 1, 0) || // Horizontal
                   dfs(r, c, 1, 0, 0) || // Vertical
                   dfs(r, c, 1, 1, 0) || // Diagonal right
                   dfs(r, c, 1, -1, 0) // Diagonal left
				{ 
                    return true
                }
            }
        }
    }
    return false
}

/*** end of file ***/
