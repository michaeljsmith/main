#ifndef __RENDERER_H__
#define __RENDERER_H__

namespace rendering
{
	class renderer
	{
	public:
		virtual void begin() = 0;
		virtual void end() = 0;
	};
}

#endif //__RENDERER_H__
