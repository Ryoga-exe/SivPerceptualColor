# pragma once
# include <Siv3D.hpp>

struct Oklab
{
	/// @brief 明度 | Lightness [0.0, 1.0]
	double l;

	/// @brief Oklab 色空間における a 軸上の距離（緑と赤の色合い） | distance along the a axis in Oklab color space [-0.4, 0.4]
	double a;

	/// @brief Oklab 色空間における b 軸上の距離（青と黄の色合い） | distance along the b axis in Oklab color space [-0.4, 0.4]
	double b;

	/// @brief アルファ | Alpha [0.0, 1.0]
	double alpha = 1.0;

	[[nodiscard]]
	Oklab() = default;

	[[nodiscard]]
	Oklab(const Oklab&) = default;

	/// @brief Oklab 色空間の色を作成します
	/// @param _l 明度
	/// @param _a a 軸上の距離（緑と赤の色合い）
	/// @param _b b 軸上の距離（青と黄の色合い）
	/// @param alpha アルファ
	[[nodiscard]]
	constexpr Oklab(double _l, double _a, double _b, double _alpha = 1.0) noexcept
		: l{ _l }
		, a{ _a }
		, b{ _b }
		, alpha{ _alpha } {}

	/// @brief Oklab 色空間の色を作成します
	/// @param oklab 色
	/// @param alpha アルファ
	[[nodiscard]]
	constexpr Oklab(const Oklab& oklab, double _alpha) noexcept
		: l{ oklab.l }
		, a{ oklab.a }
		, b{ oklab.b }
		, alpha{ _alpha } {}

	[[nodiscard]]
	Oklab(Color color) noexcept;

	[[nodiscard]]
	Oklab(const ColorF& color) noexcept;

	[[nodiscard]]
	constexpr Oklab(const Vec3& oklab, double _alpha) noexcept
		: l{ oklab.x }
		, a{ oklab.y }
		, b{ oklab.z }
		, alpha{ _alpha } {}

	[[nodiscard]]
	constexpr Oklab(const Vec4& oklabWithAlpha) noexcept
		: l{ oklabWithAlpha.x }
		, a{ oklabWithAlpha.y }
		, b{ oklabWithAlpha.z }
		, alpha{ oklabWithAlpha.z } {}

	[[nodiscard]]
	constexpr double elem(size_t index) const noexcept;

	[[nodiscard]]
	double* getPointer() noexcept;

	[[nodiscard]]
	const double* getPointer() const noexcept;

	constexpr Oklab& operator =(const Oklab&) = default;

	[[nodiscard]]
	constexpr Oklab operator +(const Oklab& oklab) const noexcept;

	[[nodiscard]]
	constexpr Oklab operator -(const Oklab& oklab) const noexcept;

	[[nodiscard]]
	friend constexpr bool operator ==(const Oklab& lhs, const Oklab& rhs) noexcept
	{
		return (lhs.l == rhs.l)
			&& (lhs.a == rhs.a)
			&& (lhs.b == rhs.b)
			&& (lhs.alpha == rhs.alpha);
	}

	[[nodiscard]]
	friend constexpr bool operator !=(const Oklab& lhs, const Oklab& rhs) noexcept
	{
		return (lhs.l != rhs.l)
			|| (lhs.a != rhs.a)
			|| (lhs.b != rhs.b)
			|| (lhs.alpha != rhs.alpha);
	}

	[[nodiscard]]
	constexpr Oklab withL(double _l) const noexcept;

	[[nodiscard]]
	constexpr Oklab withA(double _a) const noexcept;

	[[nodiscard]]
	constexpr Oklab withB(double _b) const noexcept;

	[[nodiscard]]
	constexpr Oklab withAlpha(double _alpha) const noexcept;

	constexpr Oklab& setL(double _l) noexcept;

	constexpr Oklab& setA(double _a) noexcept;

	constexpr Oklab& setB(double _b) noexcept;

	constexpr Oklab& setAlpha(double _alpha) noexcept;

	constexpr Oklab& set(double _l, double _a, double _b, double alpha = 1.0) noexcept;

	constexpr Oklab& set(const Oklab& oklab) noexcept;

	[[nodiscard]]
	constexpr Oklab lerp(const Oklab& other, double f) const noexcept;

	[[nodiscard]]
	size_t hash() const noexcept;

	[[nodiscard]]
	ColorF removeSRGBCurve() const noexcept;

	[[nodiscard]]
	ColorF applySRGBCurve() const noexcept;

	[[nodiscard]]
	Color toColor() const noexcept;

	[[nodiscard]]
	Color toColor(uint32 _alpha) const noexcept;

	[[nodiscard]]
	ColorF toColorF() const noexcept;

	[[nodiscard]]
	ColorF toColorF(double _alpha) const noexcept;

	[[nodiscard]]
	constexpr Vec3 oklab() const noexcept;

	[[nodiscard]]
	constexpr Vec4 oklabWithAlpha() const noexcept;

	template <class CharType>
	friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Oklab& value)
	{
		return output << CharType('(')
			<< value.l << CharType(',') << CharType(' ')
			<< value.a << CharType(',') << CharType(' ')
			<< value.b << CharType(',') << CharType(' ')
			<< value.alpha << CharType(')');
	}

	template <class CharType>
	friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Oklab& value)
	{
		CharType unused;
		return input >> unused
			>> value.l >> unused
			>> value.a >> unused
			>> value.b >> unused
			>> value.alpha >> unused;
	}

	[[nodiscard]]
	static constexpr Oklab Zero() noexcept;

	friend void Formatter(FormatData& formatData, const HSV& value);
};

// fmt

template <>
struct fmt::formatter<Oklab, s3d::char32>
{
	std::u32string tag;

	auto parse(basic_format_parse_context<s3d::char32>& ctx)
	{
		return s3d::detail::GetFormatTag(tag, ctx);
	}

	template <class FormatContext>
	auto format(const Oklab& value, FormatContext& ctx)
	{
		if (tag.empty())
		{
			return format_to(ctx.out(), U"({}, {}, {}, {})", value.l, value.a, value.b, value.alpha);
		}
		else
		{
			const std::u32string format
				= (U"({:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"}, {:" + tag + U"})");
			return format_to(ctx.out(), format, value.l, value.a, value.b, value.alpha);
		}
	}
};

// Hash

template <>
struct std::hash<Oklab>
{
	[[nodiscard]]
	size_t operator ()(const Oklab& value) const noexcept
	{
		return value.hash();
	}
};
