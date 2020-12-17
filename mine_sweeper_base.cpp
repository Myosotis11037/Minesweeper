#include<algorithm>
#include<iostream>
#include<cstring>
#include<functional>
#include<time.h>
#include"mine_sweeper.h"

#define equal(a,b) equal(((char*)&(b)),((char*)&(b)+sizeof(a)),((char*)&(a)))

using namespace std;

map::elem& at(map m, map::pos_t p) {
	function<bool(map, size_t, size_t)> valid = [](map m, size_t x, size_t y) {
		return x < m.width&& y < m.height;
	};

	return m.base[valid(m, p.x, p.y) ? p.y * m.width + p.x : &map::GLOBAL_INVALID_ELEMENT - m.base];
}

constexpr neighbor_view neighbors(map::pos_t p) {
	return { {
		{p.x - 1, p.y - 1}, {p.x - 1, p.y}, {p.x - 1, p.y + 1},
		{p.x, p.y - 1}, {p.x, p.y + 1},
		{p.x + 1, p.y - 1}, {p.x + 1, p.y}, {p.x + 1, p.y + 1}
	} };
}

map fillmines(map m, int mine_num, map::pos_t mineless_pos) {
	srand((int32_t)time(0));
	const map::pos_t(&n)[8] = neighbors(mineless_pos).$;

	for (intptr_t i = 0; i < mine_num; ) {
		map::pos_t p = { rand() % m.width, rand() % m.height };

		if (at(m, p) == map::elem::mine
			|| (find_if(
				&n[0], &n[8], [&](map::pos_t ip) {
					return equal(p, ip);
				}) != &n[8])
			)
		{
			continue;
		}
		else {
			i++;
			at(m, p) = map::elem::mine;
		}
	}

	return m;
}

map fillnumbers(map m) {
	function<map::elem(size_t)> element_cast = [](size_t n) {
		return map::elem(n == 0 ? ' ' : '0' + n);
	};

	for (uintptr_t x = 0; x < m.width; x++) {
		for (uintptr_t y = 0; y < m.height; y++) {
			if (at(m, map::pos_t{ x, y }) == map::elem::mine) continue;

			const map::pos_t(&n)[8] = neighbors({ x, y }).$;

			at(m, { x, y }) = element_cast(count_if(
				n, n + sizeof(n) / sizeof(*n),
				[&](map::pos_t c) {
					return at(m, c) == map::elem::mine;
				})
			);
		}
	}

	return m;
}

map createmap(int type) {
	function<map::elem* (size_t, size_t)> _newmap = [](size_t w, size_t h) {
		map::elem* ans = new map::elem[w * h];
		memset(ans, ' ', w * h * sizeof(map::elem));
		return ans;
	};

	return {
		_newmap(tt[type].w,tt[type].h),
		new intptr_t[tt[type].w * tt[type].h * sizeof(intptr_t)] {},
		tt[type].w,tt[type].h
	};
}

map initmap(map m, int type, map::pos_t mineless_pos) {
	return fillnumbers(fillmines(m, tt[type].mine_num, mineless_pos));
}

void openblock(map m, map::pos_t footprint) {
	intptr_t& uncovered = m.uncovered[footprint.y * m.width + footprint.x];

	if (uncovered == -1) return;

	bool ＲＴＬ = uncovered ||
		(at(m, footprint) != map::elem::invalid &&
			at(m, footprint) != map::elem::mine && (uncovered |= true),
			at(m, footprint) != map::elem::air);

	if (ＲＴＬ) return;

	for (map::pos_t p : neighbors(footprint).$) openblock(m, p);
}

void deletemap(map m) {
	delete[] m.base;
	delete[] m.uncovered;
}