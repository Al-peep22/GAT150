#include "Mesh.h"
#include "Renderer.h"

namespace viper {
	/// <summary>
	/// Loads mesh data from a text file, including color and points.
	/// </summary>
	/// <param name="filename">The path to the text file containing mesh data.</param>
	/// <returns>True if the mesh was loaded successfully; false otherwise.</returns>
	bool Mesh::Load(const std::string& filename) {
		std::string buffer;
		if (!file::ReadTextFile(filename, buffer)) {
			Logger::Error("Could not read file: {}", filename);
			return false;
		}

		std::stringstream stream(buffer);

		// Read color
		stream >> _color;

		// Read points
		vec2 point;
		while (stream >> point) {
			_points.push_back(point);
		}

		if (!stream.eof()) {
			Logger::Error("Could not parse file: {}", filename);
			return false;
		}

		return true;
	}

	/// <summary>
	/// Draws the mesh by rendering its points as connected lines with specified position, rotation, and scale.
	/// </summary>
	/// <param name="renderer">Reference to the Renderer object used for drawing.</param>
	/// <param name="position">The position (2D vector) where the mesh will be drawn.</param>
	/// <param name="rotation">The rotation angle in degrees to apply to the mesh.</param>
	/// <param name="scale">The scaling factor to apply to the mesh.</param>
	void Mesh::Draw(Renderer& renderer, const vec2& position, float rotation, float scale){
		// Checks if points are empty, if so then return
		if (_points.empty()) return;

		renderer.SetColor(_color.r, _color.g, _color.b);

		// Iterate through all points, draw line
		for (int i = 0; i < (_points.size() - 1); i++) {
			vec2 p1 = (_points[i].Rotate(math::degToRad(rotation)) * scale) + position;
			vec2 p2 = (_points[i + 1].Rotate(math::degToRad(rotation)) * scale) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	/// <summary>
	/// Draws the mesh using the specified renderer and transform.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the mesh.</param>
	/// <param name="transform">The transform specifying the position, rotation, and scale for drawing the mesh.</param>
	void Mesh::Draw(Renderer& renderer, const Transform& transform) {
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}

	/// <summary>
	/// Calculates and updates the radius of the mesh as the maximum distance from the origin among its points.
	/// </summary>
	void Mesh::CalculateRadius() {
		_radius = 0;
		for (auto& point : _points) {
			float length = point.Length();
			if (length > _radius) _radius = length;
		}
	}
}

