#pragma once
#include "UI/UIManager.hpp"

namespace Big::Lists
{
	inline const char* HeaderTypesFrontend[]
	{
		"Static",
		"Gradient",
		"YTD"
	};

	inline UserInterface::HeaderType HeaderTypesBackend[]
	{
		UserInterface::HeaderType::Static,
		UserInterface::HeaderType::Gradient,
		UserInterface::HeaderType::YTD
	};

	inline std::size_t HeaderTypesPosition = 1;

	inline const char* DemoList[10]
	{
		"One",
		"Two",
		"Three",
		"Four",
		"Five",
		"Six",
		"Seven",
		"Eight",
		"Nine",
		"Ten"
	};

	inline std::size_t DemoListPos = 0;
}
