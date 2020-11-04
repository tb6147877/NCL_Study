#pragma once
#include <iostream>
#include <vector>
#include <map>

#include "Unit.h"

namespace maze2 {
	class PlayerMoveController
	{
	private:
		//std::vector<Unit*> m_exits;
		std::map<Unit*, std::vector<Unit*>> m_paths;
	public:
		PlayerMoveController();
		~PlayerMoveController();


	};

}