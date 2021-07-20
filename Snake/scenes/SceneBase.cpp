#include "stdafx.h"
#include "SceneBase.h"

void game::SceneBase::init()
{
	for (auto& thread : m_threads)
	{
		thread.join();
	}
}
