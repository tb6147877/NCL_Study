#include "PlayerMoveController.h"


bool maze2::PlayerMoveController::checkPlayerCanMove(const int index) {
	std::vector<maze2::Unit*> temp{};
	Unit* cur{ nullptr };
	for (int i = 0; i < m_paths.size(); i++) {
		if (m_paths[i].size() == 0)
		{
			continue;
		}
		if (index==i)
		{
			std::queue<Unit*> x{ m_paths[i] };
			x.pop();
			if (x.size()==0)
			{
				return true;
			}
			cur = x.front();
		}
		else {
			temp.push_back(m_paths[i].front());
		}
	}

	//check the next grid player will go has a player
	return std::find(temp.begin(), temp.end(), cur) == temp.end();
}


//============================================================
maze2::PlayerMoveController::PlayerMoveController() :m_paths{}, m_curPlayer{0}{}
maze2::PlayerMoveController::~PlayerMoveController() {}

void maze2::PlayerMoveController::insertPath(const std::queue<Unit*> value) {
	m_paths.push_back(value);
}

std::vector<maze2::Unit*> maze2::PlayerMoveController::getPlayersPosition() {
	std::vector<maze2::Unit*> temp{};
	for (int i = 0; i < m_paths.size(); i++)
	{
		if (m_paths[i].size()== 0)
		{
			continue;
		}
		if (i==m_curPlayer and checkPlayerCanMove(m_curPlayer))
		{
			//this is actually do a movement
			m_paths[i].pop();
		}
		if (m_paths[i].size()>0)
		{
			temp.push_back(m_paths[i].front());
		}
	}

	//turn change
	++m_curPlayer;
	if (m_curPlayer== m_paths.size())
	{
		m_curPlayer = 0;
	}
	return temp;
}