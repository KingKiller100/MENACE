#pragma once

namespace World
{
	class iWorld
	{
	public:
		virtual ~iWorld() = default;

		virtual void Update() = 0;
		virtual void DrawMap() = 0;
		virtual void Restart() = 0;
	};
}