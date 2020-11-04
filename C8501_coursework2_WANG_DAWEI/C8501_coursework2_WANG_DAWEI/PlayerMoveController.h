#pragma once
#include <iostream>
#include <vector>
#include <queue>

#include "Unit.h"

namespace maze2 {
	//control player move
	class PlayerMoveController
	{
	private:
		//std::vector<Unit*> m_exits;
		std::vector<std::queue<Unit*>> m_paths;
		int m_curPlayer;

		//because players cannot overlay each other, so we need this function
		//para: the index of this turn who will move
		bool checkPlayerCanMove(const int index);
	public:
		PlayerMoveController();
		~PlayerMoveController();

		//store paths player will go 
		void insertPath(const std::queue<Unit*> value);

		//core function control players move in turn
		std::vector<Unit*> getPlayersPosition();
	};

}