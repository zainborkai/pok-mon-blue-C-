// M = Mom *Not going to be a part of map*
// C = Computer / PC *ITEM PC*
// N = SNES *Interact all sides*
// T = TV *Interact from bottom*
// B = Bookshelf *Interact from bottom*
// W = Wall Map
// T = Table Book *Interact from top, disappears if you talk to girl after parcel delivery*
// F = Stairs


int PlayerHouseFloorOne[8][8] = { {'B','B',0,'T',0,0,0,'F'},
								  {0,0,0,0,0,0,0,0},
								  {0,0,0,0,0,0,0,0},
								  {0,0,0,0,0,0,0,0},
								  {0,0,0,1,1,'M',0,0},
								  {0,0,0,1,1,0,0,0},
								  {0,0,0,0,0,0,0,0},
								  {0,0,0,0,0,0,0,0}, };

int PlayerHouseFloorTwo[8][8] = { { 'C',1,1,0,0,0,0,'F' },
								  { 0,0,0,0,0,0,0,0 },
								  { 0,0,0,0,0,0,0,0 },
								  { 0,0,0,0,0,0,0,0 },
							  	  { 0,0,0,0,0,0,0,0 },
								  { 0,0,0,'N',0,0,0,0 },
								  { 1,0,0,0,0,0,1,0 },
								  { 1,0,0,0,0,0,1,0 }, };

int PalletHouseOne[8][8] = { { 'B','B',0,'W',0,0,0,'B' },
						  { 0,0,0,0,0,0,0,0 },
						  { 0,0,0,0,0,0,0,0 },
						  { 0,0,0,0,0,0,0,0 },
						  { 0,0,0,'T',1,0,0,0 },
						  { 0,0,0,1,1,0,0,0 },
						  { 1,0,0,0,0,0,0,1 },
						  { 1,0,0,0,0,0,0,1 }, };


//--------------------------------------------------//