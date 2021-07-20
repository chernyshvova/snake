#include "stdafx.h"
#include "SceneBase.h"

void game::SceneBase::run()
{
	for (auto& thread : m_threads)
	{
		thread.join();
	}
}
