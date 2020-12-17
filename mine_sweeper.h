int menu();
void choose(int cmd);
void printDifficulty();

const struct {
	size_t w, h, mine_num;
} tt[3] = {
	{9,9,10},
	{16,16,40},
	{30,16,99}
};

struct map {
	enum class elem : char {
		air = ' ',
		I = '1', II = '2', III = '3',
		IV = '4', V = '5', VI = '6',
		VII = '7', VIII = '8',
		mine = '*',
		invalid = '?'
	} *base = nullptr;

	intptr_t* uncovered = nullptr;

	struct pos_t {
		size_t x, y;
	};

	static constexpr pos_t GLOBAL_INVALID_POS = { size_t(-2), size_t(-2) }; 
	static const elem GLOBAL_INVALID_ELEMENT = elem::invalid; 


	size_t width = 0, height = 0;
};

struct neighbor_view { map::pos_t $[8]; };

map createmap(int type);
void deletemap(map);
map::elem& at(map, map::pos_t);
map initmap(map, int type, map::pos_t);
void printui(map);
void printgraphui(map m);
void printmap(map, int coverage = 1, bool highlight = true);
void printgraphmap(map m, int coverage = 1, bool highlight = true);
void Mark(map m, map::pos_t footprint);
void UnMark(map m, map::pos_t footprint);
map::pos_t getOperate(map);
void exPrint();
void printhalt();
void openblock(map, map::pos_t);
void operate3(map m, int s);
void operate4(map m, int s);
void operate6(map m, int& x, int& y);
void operate8(map m, int s);
void operate9(map m, int s);
void getcursorpos(map m, int& x, int& y);
char getOpt(map m);
map::pos_t gettwoopt(map m);
size_t getlastopt(map m);
int judge(map m, map::pos_t footprint, int s);
