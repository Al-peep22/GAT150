#pragma once

#include "Math/Vector3.h"
#include "Math/Transform.h"
#include "Resources/Resource.h"

#include <vector>

namespace viper {
	class Mesh : public Resource {
	public:
		Mesh() = default;
		Mesh(const std::vector<vec2> points, const vec3& color) :
			_points{ points },
			_color{ color }
		{
			CalculateRadius();
		}

		bool Load(const std::string& filename);

		void Draw(class Renderer& renderer, const vec2& position,float rotation, float scale);
		void Draw(class Renderer& renderer, const Transform& transform);

		float GetRadius() const { return _radius; }

	private:
		void CalculateRadius();

	private:
		float _radius{ 0 };
		std::vector<vec2> _points;
		vec3 _color{ 1, 1, 1 };
	};
}