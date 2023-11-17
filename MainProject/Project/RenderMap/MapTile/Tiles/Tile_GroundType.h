#pragma once

enum class GroundTypeVertical {
	Top,
	Middle,
	Bottom,
};

enum class GroundTypeHorizontal {
	Left,
	Center,
	Right
};

struct GroundTypes {
	/// <summary>
	/// …•½•ûŒü
	/// </summary>
	GroundTypeHorizontal	horizontal;

	/// <summary>
	/// ‚’¼•ûŒü
	/// </summary>
	GroundTypeVertical		vertical;

	GroundTypes(
		GroundTypeHorizontal h = GroundTypeHorizontal::Left,
		GroundTypeVertical v = GroundTypeVertical::Top
	) {
		horizontal = h;
		vertical = v;
	}
};