#pragma once

#ifndef PE_SHAPE_COMPONENT_GUARD
#define PE_SHAPE_COMPONENT_GUARD

#include <memory>
#include <vector>

#include <Maths/Shapes/Shape.hpp>

#include <SDK/Scene/Components/Component.hpp>

namespace Pe
{
	struct ShapeHandle
	{
		const Shape* shape = nullptr;
		unsigned int vertexBufferID = 0;

		static std::shared_ptr<ShapeHandle> Create(const Shape* _shape);
	};

	class ShapeComponent : public Component
	{
		std::vector<Vec2> mWorldPoints;

		std::shared_ptr<ShapeHandle> mHandle;

	public:
		ShapeComponent(GameObj* _obj, const Shape* _shape) noexcept;
		ShapeComponent(GameObj* _obj, std::shared_ptr<ShapeHandle> _shapeHandle) noexcept;

		std::shared_ptr<ShapeHandle> GetHandle() const;
		const std::vector<Vec2>& GetPoints() const noexcept;

		bool IsPointInside(Vec2 _point) const noexcept;

		float ComputeShapeIntertia() const;
		Vec2 ComputeCentroid() const;

		void Update(float _frameTime) noexcept override;
	};
}

#endif // GUARD